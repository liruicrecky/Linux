/*************************************************************************
	> File Name: 1.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Thu 05 Mar 2015 11:23:10 PM CST
 ************************************************************************/

void serverGetFiles(int clientFd, char *para)
{
	//get path

	char filePath[128];
	memset(filePath, 0, 128);

	ssprintf(filePath, "%s/%s", getcwd(NULL, 0), para);
	printf("%s\n, filePath");

	//opdir
	
	DIR *pDIR;
	struct dirent *dirInfo;
	struct stat fileStat;
	char serFileInfoBuf[1024];

	if((pDIR = opendir(filepath)) == NULL)
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

void clientDownloadFiles(int clientSocket, char *buf, int flag)
{
	char fileName[20];
	char filePath[128];
	char userPath[128];

	unsigned long fileSize;

	MSG recvMsg;

	//if user path

	if(flag == 1)
	{
		sscanf(buf, "%s/%s", filePath, fileName);
		memset(userPath, 0, 128);
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

	int dir;

	while(memset(&recvMsg, 0, sizeof(recvMsg)), recv(clientSocket, &recvMsg, sizeof(clientMsg), 0))
	{
		int dir;

		sscanf(recvMsg.buf, "%s %lu %d", fileName, &fileSize, &dir);

		if(flag != 1)
		{
			memset(filePath, 0, 128);
			sprintf(filePath, "%s/%s", getcwd(NULL, 0), fileName);
		}
		
		printf("%s\n", fileName);

		printf("%s\n", filePath);

		if(dir == 1)
		{
			mkdir(filePath, 0777);
			chdir(filePath);
			clientDownLoadFile(clientSocket, filePath, 0);
			chdir("..");
		}
		else
		{

			unsigned long recvFileSize = 0;
			unsigned long writeFileSize;
			
			printf("File size: %lu\n", fileSize);

			//create a new file 

			int serverFile = open(filePath, O_WRONLY | O_CREAT);

			//recv file from server

			while(recvFileSize < fileSize)
			{
				memset(&recvMsg, 0, sizeof(recvMsg));
				frecvBuf(clientSocket, (char *)&recvMsg, sizeof(recvMsg));
				recvFileSize += recvMsg.msgLen;
				write(serverFile, recvMsg.buf, recvMsg.msgLen);
			}
	
			if(fileSize == getFileSize(filePath))
			{
				printf("Downloaded file from server successfully!\n");
				printf("File path:%s\n", filePath);
			}

			close(serverFile);

			fgetc(stdin);

			printf("before chidr--path:%s\n", getcwd(NULL, 0));
		}
		
	}

}


