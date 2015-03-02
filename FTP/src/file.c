/*************************************************************************
	> File Name: ./src/file.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Mon 02 Mar 2015 10:28:47 AM CST
 ************************************************************************/

#include"ftp.h"

void serverLs(int clientFd)
{
	//get path
	char serPath[128];
	memset(serPath, 0, 128);

	strcpy(serPath, getcwd(NULL, 0));

	//get dir
	
	DIR *pDIR;
	struct dirent *dirInfo;
	struct stat fileStat;
	MSG sendClientMsg;
	char serFileInfoBuf[1024];

	if((pDIR = opendir(serPath)) == NULL)
	{
		perror("opendir");
	}

	chdir(serPath);

	while(memset(serFileInfoBuf, 0, 1024), (dirInfo = readdir(pDIR)) != NULL)
	{
		if(strcmp(dirInfo -> d_name, ".") == 0 || strcmp(dirInfo -> d_name, "..") == 0)
		{
			continue;
		}

		//get file stat

		stat(dirInfo -> d_name, &fileStat);

		//put info into buf

		sprintf(serFileInfoBuf, "%s %u", dirInfo -> d_name, fileStat.st_size);
		//send buf
		sendClientMsg.msgLen = strlen(serFileInfoBuf);
		strcpy(sendClientMsg.buf, serFileInfoBuf);
		send(clientFd, &sendClientMsg, sizeof(sendClientMsg), 0);

	/*	if(dirInfo -> d_type & DT_DIR)
			printf("\033[34m%10s\033[0m	%10u\n", dirInfo -> d_name, fileStat.st_size);
		else
			printf("%10s	%10u\n", dirInfo -> d_name, fileStat.st_size);
	*/
	}
	//end
	memset(&sendClientMsg, 0, sizeof(sendClientMsg));
	sendClientMsg.msgLen = 3;
	strcpy(sendClientMsg.buf, "end");
	send(clientFd, &sendClientMsg, sizeof(sendClientMsg), 0);

}

void serverPwd(int clientFd)
{
	char serverPath[128];
	memset(serverPath, 0, 128);

	strcpy(serverPath, getcwd(NULL, 0));

	send(clientFd, serverPath, strlen(serverPath), 0);
}

void serverCd(int clientFd, char *para)
{
	if(strncmp(para, "..", 2) == 0)
		chdir("..");
	else
		chdir(para);
}


void serverGetFiles(int clientFd, char *para)
{
	//get file path

	char filePath[128];
	memset(filePath, 0, 128);

	sprintf(filePath, "%s/%s", getcwd(NULL, 0), para);
	printf("%s\n", filePath);

	//open file
	
	char buf[1024];
	int serverFile = open(filePath, O_RDONLY);
	if(serverFile == -1)
	{
		strcpy(buf, "can't find the file on server!'");
		send(clientFd, buf, strlen(buf), 0);
		return;
	}

	//get file size and send to client
	
	unsigned long serverFileSize = getFileSize(filePath);

	send(clientFd, &serverFileSize, sizeof(&serverFileSize), 0);

	//mmap
	
	char *mmapFile;

	mmapFile = mmap(NULL, serverFileSize, PROT_READ, MAP_PRIVATE, serverFile, 0);

	close(serverFile);

	//send package

	MSG sendBuf;
	unsigned long readFileSize;
	unsigned long totalSendFileSize = 0;

	while(memset(&sendBuf, 0, sizeof(sendBuf)), totalSendFileSize < serverFileSize)
	{
		readFileSize = 0;
		while(readFileSize < 1024 && totalSendFileSize < serverFileSize)
		{
			*(sendBuf.buf + readFileSize) = *(mmapFile + totalSendFileSize);
			++totalSendFileSize;
			++readFileSize;
		}
		sendBuf.msgLen = readFileSize;
		fsendBuf(clientFd, (char *)&sendBuf, sizeof(sendBuf));
	}

	munmap(mmapFile, serverFileSize);
	
}

void serverPutFiles(int clientFd, char *para)
{
	//recv file size from client
	
	unsigned long fileSize;
	recv(clientFd, &fileSize, sizeof(&fileSize), 0);

	//create a new file
	
	char filePath[128];
	sprintf(filePath, "%s/%s", getcwd(NULL, 0), para);

	int uplodeFile = open(filePath, O_WRONLY | O_CREAT);

	//recv file form client
	
	MSG fileBuf;

	unsigned long recvFileSize = 0;
	unsigned long writeFileSize;

	while(recvFileSize < fileSize)
	{
		memset(&fileBuf, 0, sizeof(fileBuf));
		frecvBuf(clientFd, (char *)&fileBuf, sizeof(fileBuf));
		recvFileSize += fileBuf.msgLen;
		write(uplodeFile, fileBuf.buf, fileBuf.msgLen);
		printf("recv : %lu\n", recvFileSize);
	}

}

void serverRemove(int clientFd, char *para)
{
	//get file path
	
	char filePath[128];;
	sprintf(filePath, "%s/%s", getcwd(NULL, 0), para);

	remove(filePath);

}

unsigned long getFileSize(char *path)
{
	struct stat fdFile;
	unsigned long fileSize;

	memset(&fdFile, 0, sizeof(fdFile));

	if(stat(path, &fdFile) == -1)
	{
		perror("getFileStat");
		return 0;
	}

	fileSize = fdFile.st_size;

	return fileSize;
}

unsigned long fsendBuf(int socket, char *buf, int len)
{
	unsigned long sendSum = 0;
	while(sendSum < len)
		sendSum += send(socket, buf + sendSum, len - sendSum, 0);

	return sendSum;
}

unsigned long frecvBuf(int socket, char *buf, int len)
{
	unsigned long recvSum = 0;
	while(recvSum < len)
		recvSum += recv(socket, buf + recvSum, len - recvSum, 0);

	return recvSum;
}
