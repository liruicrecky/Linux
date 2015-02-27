/*************************************************************************
	> File Name: ./client.c
	> Author: Recky
	> Mail:327763224@qq.com 
	> Created Time: Sun 08 Feb 2015 02:38:09 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/stat.h>

#define SERVER_IP "192.168.1.49" 
#define PATH "/home/liruicheng/LinuxCode/20150208/tcpserver"
#define FILE_PATH "Clean-Code.pdf"
#define FILE_NA "The.pdf"

unsigned long fsendBuf(int serverSocket, char *buf, unsigned long length);
unsigned long frecvBuf(int serverAccept, char *buf, unsigned long length);

int main(int argc, char *argv[])
{
	//socket
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket == -1)
	{
		perror("init client socket failed");
		exit(1);
	}

	//connect
	struct sockaddr_in serverSockAddr;
	memset(&serverSockAddr, 0, sizeof(struct sockaddr_in));

	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_port = htons(1234);
	serverSockAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	int clientConnect = connect(clientSocket, (struct sockaddr *)&serverSockAddr, sizeof(struct sockaddr));
	if(clientConnect == -1)
	{
		perror("connect to server failed");
		close(clientSocket);
		exit(1);
	}

	//send
	char send_buf[1024];
	memset(send_buf, 0, 1024);
/*	send_buf = (int *)calloc(1000 * 1024, sizeof(int));

	fsendBuf(clientSocket, (char *)send_buf, 1000 * 1024);
	printf("size: %d\n", sizeof(send_buf));
*/	
	sprintf(send_buf, "%s/%s", PATH, FILE_PATH);
//	strcpy(send_buf, "client  \033[32monline\033[0m\n");

	if(send(clientSocket, send_buf, strlen(send_buf), 0) == -1)
	{
		perror("send msg to server failed");
		close(clientSocket);
		exit(1);
	}


	//recv
	char recv_buf[1024];
	memset(recv_buf, 0, 1024);

	if(recv(clientSocket, recv_buf, 1024, 0) == -1)
	{
		perror("recv form server failed");
		close(clientSocket);
		exit(1);
	}
	
	int filesize, currFileSize = 0, recvfilesize;
	char path[128];
	sscanf(recv_buf, "%lu", &filesize);
	printf("filesize :%lu\n", filesize);
	sprintf(path, "%s/%s", PATH, FILE_NA);

	FILE *writeFile = fopen(path, "wb+");
	unsigned long size;
	while(currFileSize < filesize)
	{
		size = 0;
		recv(clientSocket, &size, sizeof(size), 0);
		printf("size: %lu\n", size);
		memset(recv_buf, 0, 1024);
		recvfilesize = frecvBuf(clientSocket, recv_buf, size);
		currFileSize += recvfilesize;
		printf("%lu\n", currFileSize);
		fwrite(recv_buf, sizeof(char), recvfilesize, writeFile);
	}

	fclose(writeFile);
	close(clientSocket);

	return 0;
}


unsigned long fsendBuf(int serverSocket, char *buf, unsigned long length)
{
	unsigned long send_sum = 0;
	unsigned long alreadySend;
	while(send_sum < length)
	{
		alreadySend = send(serverSocket, buf + send_sum, length - send_sum, 0);
		send_sum += alreadySend;
	}
	return send_sum;
}

unsigned long frecvBuf(int serverAccept, char *buf, unsigned long length)
{
	unsigned long recv_sum = 0;
	unsigned long alreadyRecv;
	while(recv_sum < length)
	{
		alreadyRecv = recv(serverAccept, buf + recv_sum, length - recv_sum, 0);
	//	printf("recv: %s\n", buf + recv_sum);
		recv_sum += alreadyRecv;
	}
//	printf("recv_cnt : %d\n", cnt);
	return recv_sum;
}

