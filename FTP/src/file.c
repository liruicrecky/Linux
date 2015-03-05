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

	memset(&sendClientMsg, 0, sizeof(sendClientMsg));

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

		sprintf(serFileInfoBuf, "%s %lu %c", dirInfo -> d_name, fileStat.st_size, dirInfo -> d_type);

		//send buf
		
		sendClientMsg.msgLen = strlen(serFileInfoBuf);
		strcpy(sendClientMsg.buf, serFileInfoBuf);
		send(clientFd, &sendClientMsg, sizeof(sendClientMsg), 0);

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
	//get path

	char filePath[128];
	memset(filePath, 0, 128);

	sprintf(filePath, "%s/%s", getcwd(NULL, 0), para);
	printf("%s\n, filePath");

	//opdir
	
	DIR *pDIR;
	struct dirent *dirInfo;
	struct stat fileStat;
	char serFileInfoBuf[1024];

	if((pDIR = opendir(filePath)) == NULL)
	{
		perror("opendir");
		exit(1);
	}

	chdir(filePath);

	//define send buf
	
	MSG sendMsg;
	int dir;
	unsigned long fileSize;

	while(memset(serFileInfoBuf, 0, 1024), (dirInfo = readdir(pDIR)) != NULL)
	{
		
		if(strcmp(dirInfo -> d_name, ".") == 0 || strcmp(dirInfo -> d_name, "..") == 0)
			continue;

		stat(dirInfo -> d_name, &fileStat);

		if(dirInfo -> d_type & DT_DIR)
		{
			dir = 1;

			sprintf(serFileInfoBuf, "%s %lu %d", dirInfo -> d_name, fileStat.st_size, dir);

			//send buf

			memset(&sendMsg, 0, sizeof(sendMsg));
				
			sendMsg.msgLen = strlen(serFileInfoBuf);
			strcpy(sendMsg.buf, serFileInfoBuf);
			send(clientFd, &sendMsg, sizeof(sendMsg), 0);
			
			serverGetFiles(clientFd, dirInfo -> d_name);

			chdir("..");
		}
		else
		{
	
			//open file	
	
			char buf[1024];
			int serverFile = open(filePath, O_RDONLY);

			unsigned long serverFileSize = fileStat.st_size;

			if(serverFile == -1)
			{
				serverFileSize = -1;
				send(clientFd, &serverFileSize, sizeof(&serverFileSize), 0);
			}

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

	}
}


void serverPutFiles(int clientFd, char *para)
{
	//recv file size from client
	
	unsigned long fileSize;

	recv(clientFd, &fileSize, sizeof(&fileSize), 0);

	if(fileSize == -1)
	{
		return;
	}

	//create a new file
	
	char filePath[128];
	sprintf(filePath, "%s/%s", getcwd(NULL, 0), para);

	int uploadFile = open(filePath, O_WRONLY | O_CREAT);

	//recv file form client
	
	MSG fileBuf;

	unsigned long recvFileSize = 0;
	unsigned long writeFileSize;

	while(recvFileSize < fileSize)
	{
		memset(&fileBuf, 0, sizeof(fileBuf));
		frecvBuf(clientFd, (char *)&fileBuf, sizeof(fileBuf));
		recvFileSize += fileBuf.msgLen;
		write(uploadFile, fileBuf.buf, fileBuf.msgLen);
		printf("recv : %lu\n", recvFileSize);
	}

	if(getFileSize(filePath) == fileSize)
	{
		send(clientFd, &fileSize, sizeof(&fileSize), 0);
	}

	close(uploadFile);

}

void serverRemove(int clientFd, char *para)
{
	//get file path
	
	char filePath[128];;
	int flag;

	sprintf(filePath, "%s/%s", getcwd(NULL, 0), para);

	if(unlink(filePath) == -1)
		flag = 0;
	else
		flag = 1;

	send(clientFd, &flag, sizeof(&flag), 0);

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

void delSpace(char *str)
{
	int i, j;
	for(i = 0;str[i] != '\0';i++)
		while((str[i] == ' ' && str[i + 1] == ' ') || str[0] == ' ')
			for(j = i;str[j] != '\0';j++)
				str[j] = str[j + 1];
}

int getWordNum(char *str)
{
	int i;
	int num = 0, word = 0;

	for(i = 0;str[i] != '\0';i++)
	{
		if(str[i] == ' ')
			word = 0;
		else if(word == 0)
		{
			word = 1;
			++num;
		}
	}

	return num;
}

int isDir(char *path)
{
	struct stat fileStat;
	memset(&fileStat, 0, sizeof(fileStat));

	if(stat(path, &fileStat) == -1)
	{
		return -1;
	}

	if(S_ISDIR(fileStat.st_mode))
		return 1;
	
	return 0;
}
		

void clientDownLoadFile(int clientSocket, char *buf, int flag)
{

		char fileName[20];
		char filePath[128];

		unsigned long fileSize;
		unsigned long recvFileSize = 0;
		unsigned long writeFileSize;

		MSG clientMsg;
		//get save file path

		//first recv
		char userPath[128];

		if(flag == 1)
		{
			sscanf(buf, "%s %s", filePath, fileName);
			printf("Download path(use absolute path)(input 0 for current directory):");
			scanf("%s", userPath);
			if(userPath[0] != '0')
			{
				sprintf(filePath, "%s/%s", userPath, fileName);
				chdir(userPath);
			}
			else
			{
				sprintf(filePath, "%s/%s", getcwd(NULL, 0), fileName);
				printf("%s\n", filePath);
			}
		}

		//recv file size and isDir
		
		memset(&clientMsg, 0, sizeof(clientMsg));
		recv(clientSocket, &clientMsg, sizeof(clientMsg), 0);

		int dir;

		sscanf(clientMsg.buf, "%s %lu %d", fileName, &fileSize, &dir);

		if(flag != 1)
		{
			memset(filePath, 0, 128);
			sprintf(filePath, "%s/%s", getcwd(NULL, 0), fileName);
		}

		printf("%s\n", fileName);

		printf("%s\n", filePath);

		if(fileSize == -1)
		{
			printf("open file failed!\n");
			return;
		}
		if(dir == 1)
		{
			mkdir(filePath, 0777);
			chdir(filePath);
			clientDownLoadFile(clientSocket, filePath, 0);
		}
		else
		{
			printf("File size: %lu\n", fileSize);

			//create a new file 

			int serverFile = open(filePath, O_WRONLY | O_CREAT);

			//recv file from server

			while(recvFileSize < fileSize)
			{
				memset(&clientMsg, 0, sizeof(clientMsg));
				frecvBuf(clientSocket, (char *)&clientMsg, sizeof(clientMsg));
				recvFileSize += clientMsg.msgLen;
				write(serverFile, clientMsg.buf, clientMsg.msgLen);
			}
	
			if(fileSize == getFileSize(filePath))
			{
				printf("Downloaded file from server successfully!\n");
				printf("File path:%s\n", filePath);
			}

			close(serverFile);

			fgetc(stdin);

			printf("before chidr--path:%s\n", getcwd(NULL, 0));
			chdir("..");
			printf("before chidr--path:%s\n", getcwd(NULL, 0));
		}

}


