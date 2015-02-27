/*************************************************************************
	> File Name: server.c
	> Author: Recky
	> Mail:327763224@qq.com 
	> Created Time: Sun 08 Feb 2015 11:42:32 AM CST
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
#define FILE_PATH "The_Holy_Bible_bak.txt"


unsigned long fsendBuf(int serverSocket, char *buf, unsigned long length);
unsigned long frecvBuf(int serverAccept, char *buf, unsigned long length);

int main(int argc, char *argv[])
{
	//socket
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(serverSocket == -1)
	{
		perror("inie server_socket failed");
		exit(1);
	}

	//bind
	struct sockaddr_in serverSockAddr;
	memset(&serverSockAddr, 0, sizeof(struct sockaddr_in));

	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_port = htons(1234);
	serverSockAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	int serverBind = bind(serverSocket,(struct sockaddr *)&serverSockAddr, sizeof(struct sockaddr));
	if(serverBind == -1)
	{
		perror("init server_bind failed");
		close(serverSocket);
		exit(1);
	}

	//listen
	int serverListen = listen(serverSocket, 10);
	if(serverListen == -1)
	{
		perror("init server_listen failed");
		close(serverSocket);
		exit(1);
	}

	
	//accept
	struct sockaddr_in clientSockAddr;
	memset(&clientSockAddr, 0, sizeof(struct sockaddr_in));

	socklen_t clientSockAddrLen = sizeof(struct sockaddr_in);

	int serverAccept = accept(serverSocket, (struct sockaddr *)&clientSockAddr, &clientSockAddrLen);
	if(serverAccept == -1)
	{
		perror("init serverAccept failed");
		close(serverSocket);
		exit(1);
	}
	printf("client: %s : %d successfully connected to the server\n", inet_ntoa(clientSockAddr.sin_addr), ntohs(clientSockAddr.sin_port));

	//recv
	char recv_buf[1024];
	memset(recv_buf, 0, 1024);

	if(recv(serverAccept, recv_buf, 1024, 0) == -1)
	{
		perror("recv form client failed");
		close(serverSocket);
		exit(1);
	}
	puts(recv_buf);

	struct stat f_stat;

	stat(recv_buf, &f_stat);

	FILE *openFile = fopen(recv_buf, "rb");

	//send
	char send_buf[1024];
	memset(send_buf, 0, 1024);
//	strcpy(send_buf, "welcome to the server\n");
	sprintf(send_buf, "%lu", f_stat.st_size);

	if(send(serverAccept, send_buf, strlen(send_buf), 0) == -1)
	{
		perror("send msg to client failed");
		close(serverSocket);
		exit(1);
	}

	unsigned long alsedbuf;
	unsigned long alsedsum = -1;
	while(memset(send_buf, 0, 1024), (alsedbuf = fread(send_buf, sizeof(char), 1024, openFile)) != 0)
	{
		send(serverAccept, &alsedbuf, sizeof(alsedbuf), 0);
		fsendBuf(serverAccept, send_buf, alsedbuf);
		alsedsum += alsedbuf;
	}

	printf("%lu\n", alsedsum);
	fclose(openFile);
	close(serverSocket);

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

