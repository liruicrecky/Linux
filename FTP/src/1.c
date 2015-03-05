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


