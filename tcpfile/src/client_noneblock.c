/*************************************************************************
	> File Name: ./client.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Tue 10 Feb 2015 04:37:55 PM CST
 ************************************************************************/

#include"tcp.h"

#define SER_PATH "/home/liruicheng/LinuxCode/tcpfile"

int main(int argc, char *argv[])
{
	char ip[32];
	int port;

	strcpy(ip, argv[1]);
	port = atoi(argv[2]);

	int clientServer = connectServer(ip, port);

	//send file path
	
	char buf[10240];
	memset(buf, 0, 10240);

	sprintf(buf, "%s/%s", SER_PATH, argv[3]);
	send(clientServer, buf, strlen(buf), 0);

	//get file size

	unsigned long fileSize = 0;
	recv(clientServer, &fileSize, sizeof(&fileSize), 0);
	printf("File size: %lu\n", fileSize);

	//recv file
	memset(buf, 0, 10240);
	sprintf(buf, "./bak_%s", argv[3]);
	int serFile = open(buf, O_WRONLY | O_CREAT);

	//set-nonblock
	
	setNoneBlock(clientServer);

	unsigned long recvSum = 0;
	unsigned long recvStat;

	while(1)
	{
		memset(buf, 0, 10240);
		recvStat = frecvNonBlock(clientServer, buf);
		recvSum += recvStat;
		printf("recv: %u\n", recvSum);
		write(serFile, buf, recvStat);
		if(recvSum == fileSize)
		{
			printf("downfile successfully\n");
			break;
		}
	}


	/*
	
	unsigned long recvFileSize = 0;
	unsigned long writeFileSize;
	unsigned long packageSize;

	while(recvFileSize < fileSize)
	{
		recv(clientServer, &packageSize, sizeof(&packageSize), 0);
		memset(buf, 0, 10240);
		recvFileSize += frecvBuf(clientServer, buf, packageSize);
		write(serFile, buf, packageSize);
		printf("recv size :%lu\n", recvFileSize);
	}
	*/

	close(serFile);
	close(clientServer);

	return 0;
}
