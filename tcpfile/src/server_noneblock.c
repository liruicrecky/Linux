/*************************************************************************
	> File Name: ./server.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Tue 10 Feb 2015 03:21:19 PM CST
 ************************************************************************/

#include"tcp.h"

void child_handle(int signum);

void child_handle(int signum)
{
	wait(NULL);
}

int main(int argc, char *argv[])
{
	signal(17, child_handle);
	char ip[32];
	int port;

	strcpy(ip, argv[1]);
	port = atoi(argv[2]);

	int serversock = socketInit(ip, port);

	while(1)
	{

		int clientaccept = acceptSocket(serversock);

		if(fork() == 0)
		{

			char buf[10240];
			memset(buf, 0, 10240);
			recv(clientaccept, buf, 10240, 0);
			puts(buf);

			//open file on server and get file size
	
			int serFile = open(buf, O_RDONLY);
			if(serFile == -1)
			{
				perror("open server file failed");
				exit(1);
			}

			unsigned long serFileSize = getFileSize(buf);
			printf("file size: %lu\n", serFileSize);

			send(clientaccept, &serFileSize, sizeof(&serFileSize), 0);

			//mmap
			
			char *mmapFile;

			mmapFile = mmap(NULL, serFileSize, PROT_READ, MAP_SHARED, serFile, 0);

			close(serFile);
			
			//send file package
			
			
			//mmap send

			unsigned long readFileSize;
			unsigned long totalSendFileSize = 0;

			while(memset(buf, 0, 10240), totalSendFileSize < serFileSize)
			{
				readFileSize = 0;
				while(readFileSize < 10240 && totalSendFileSize < serFileSize)
				{
					*(buf + readFileSize) = *(mmapFile + totalSendFileSize);
					++totalSendFileSize;
					++readFileSize;
				}
				send(clientaccept, buf, readFileSize, 0);
			//	send(clientaccept, &readFileSize, sizeof(&readFileSize), 0);
			//	fsendBuf(clientaccept, buf, readFileSize);
				
			}

			// i/o opertion

			/*
			while(memset(buf, 0, 1024),(readFileSize = read(mmapFile, buf, 1024)) != 0)
			{
				send(clientaccept, &readFileSize, sizeof(&readFileSize), 0);
				totalSendFileSize += fsendBuf(clientaccept, buf, readFileSize);
			}

			*/
	
			printf("send file size: %lu\n", totalSendFileSize);

			munmap(mmapFile, serFileSize);
		}
		close(clientaccept);
	}

	close(serversock);

	return 0;

}
