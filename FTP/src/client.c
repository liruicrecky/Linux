/*************************************************************************
	> File Name: ./src/client.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Sun 01 Mar 2015 09:36:39 PM CST
 ************************************************************************/

#include"ftp.h"

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("error cmd in argv\n");
		exit(1);
	}
	//socket
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket == -1)
	{
		perror("client socket");
		exit(1);
	}

	//connect
	
	struct sockaddr_in clientSockAddr;
	memset(&clientSockAddr, 0, sizeof(clientSockAddr));

	clientSockAddr.sin_family = AF_INET;
	clientSockAddr.sin_port = htons(atoi(argv[2]));
	clientSockAddr.sin_addr.s_addr = inet_addr(argv[1]);

	if(connect(clientSocket, (struct sockaddr *)&clientSockAddr, sizeof(struct sockaddr)) == -1)
	{
		perror("client connect");
		close(clientSocket);
		exit(1);
	}

	char buf[1024];
	char fileName[20];
	char filePath[128];

	unsigned long fileSize;
	unsigned long recvFileSize = 0;
	unsigned long writeFileSize;

	MSG clientMsg;
	memset(buf, 0, sizeof(buf));
	recv(clientSocket, buf, 1024, 0);
	printf("from server:%s\n", buf);

	while(memset(buf, 0, 1024), printf("#"), fgets(buf, 1024, stdin) != NULL)
	{
		//if command "ls"

		if(strncmp(buf, "ls", 2) == 0)
		{
			send(clientSocket, buf, strlen(buf), 0);
			while(memset(&clientMsg, 0, sizeof(clientMsg)), recv(clientSocket, &clientMsg, sizeof(clientMsg), 0) != 0)
			{
				if(strncmp(clientMsg.buf, "end", 3) == 0)
				{
					break;
				}				
				sscanf(clientMsg.buf, "%s %u", fileName, &fileSize);
				printf("%-10s	%-10u\n", fileName, fileSize);	
			}
		}
		//if command "pwd"

		else if(strncmp(buf, "pwd", 3) == 0)
		{
			send(clientSocket, buf, strlen(buf), 0);
			memset(buf, 0, 1024);
			recv(clientSocket, buf, 1024, 0);
			printf("path: %s\n", buf);
		}
		//if command "cd "
		
		else if(strncmp(buf, "cd", 2) == 0)
		{
			send(clientSocket, buf, strlen(buf), 0);
		}
		//if command "gets "

		else if(strncmp(buf, "gets", 3) == 0)
		{
			send(clientSocket, buf, strlen(buf), 0);

			//recv file size

			recv(clientSocket, &fileSize, sizeof(&fileSize), 0);
			printf("file size: %u\n", fileSize);

			//create a new file 

			sscanf(buf, "%s %s", filePath, fileName);
			sprintf(filePath, "./%s", fileName);
			int serverFile = open(filePath, O_WRONLY | O_CREAT);

			//recv file from server

			while(recvFileSize < fileSize)
			{
				memset(&clientMsg, 0, sizeof(clientMsg));
				frecvBuf(clientSocket, (char *)&clientMsg, sizeof(clientMsg));
				recvFileSize += clientMsg.msgLen;
				write(serverFile, clientMsg.buf, clientMsg.msgLen);
				printf("recv : %lu\n", recvFileSize);
			}
			
		}
		//if command "puts"

		else if(strncmp(buf, "puts", 3) == 0)
		{
			send(clientSocket, buf, strlen(buf), 0);

			//open file and get file size and send file size

			sscanf(buf, "%s %s", filePath, fileName);
			sprintf(filePath, "%s/%s", getcwd(NULL, 0), fileName);

			printf("%s\n", filePath);

			int clientFile = open(filePath, O_RDONLY);
			if(clientFile == -1)
			{
				perror("open file");
				continue;
			}

			fileSize = getFileSize(filePath);
			printf("filesize:%lu\n", fileSize);

			send(clientSocket, &fileSize, sizeof(&fileSize), 0);

			//mmap

			char *mmapFile;

			mmapFile = mmap(NULL, fileSize, PROT_READ, MAP_PRIVATE, clientFile, 0);
			
			close(clientFile);

			//send package

			MSG sendBuf;
			unsigned long readFileSize;
			unsigned long totalSendFileSize = 0;

			while(memset(&sendBuf, 0, sizeof(sendBuf)), totalSendFileSize < fileSize)
			{
				readFileSize = 0;
				while(readFileSize < 1024 && totalSendFileSize < fileSize)
				{
					*(sendBuf.buf + readFileSize) = *(mmapFile + totalSendFileSize);
					++totalSendFileSize;
					++readFileSize;
				}
				sendBuf.msgLen = readFileSize;
				fsendBuf(clientSocket, (char *)&sendBuf, sizeof(sendBuf));
			}
		
			munmap(mmapFile, fileSize);

		}
		//if command "remove"
		//
		else if(strncmp(buf, "remove", 6) == 0)
		{
			send(clientSocket, buf, strlen(buf), 0);
		}

		if(buf[0] == 'q')
			break;
	}

	close(clientSocket);

	return 0;
}
