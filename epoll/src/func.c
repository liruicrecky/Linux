/*************************************************************************
	> File Name: ./src/func.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Fri 27 Feb 2015 11:09:15 AM CST
 ************************************************************************/

#include"epoll.h"
#define LISTEN_NUM 10

int initServerSocket(char *ip, int port)
{
	//socket
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(serverSocket == -1)
	{
		perror("server socket");
		exit(1);
	}

	//bind
	
	struct sockaddr_in serverSockAddr;
	memset(&serverSockAddr, 0, sizeof(serverSockAddr));

	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_port = htons(port);
	serverSockAddr.sin_addr.s_addr = inet_addr(ip);

	if(bind(serverSocket, (struct sockaddr *)&serverSockAddr, sizeof(struct sockaddr)) == -1)
	{
		perror("server bind");
		close(serverSocket);
		exit(1);
	}

	//listen
	 if(listen(serverSocket, LISTEN_NUM) == -1)
	 {
		perror("server listen");
		exit(1);
	 }

	 return serverSocket;
}

int serverSockAccept(int serverSocket)
{
	//accept
	struct sockaddr_in clientSockAddr;
	memset(&clientSockAddr, 0, sizeof(clientSockAddr));

	socklen_t clientSockAddrLen = sizeof(struct sockaddr_in);

	int serverAccept = accept(serverSocket, (struct sockaddr *)&clientSockAddr, &clientSockAddrLen);
	if(serverAccept == -1)
	{
		perror("client accept");
		exit(1);
	}

	printf("client: %s:%d has connected server successfully\n", inet_ntoa(clientSockAddr.sin_addr), ntohs(clientSockAddr.sin_port));

	return serverAccept;
}

//connect

int clientConnectServer(char *ip, int port)
{
	//socket
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket == -1)
	{
		perror("client socket");
		exit(1);
	}
	
	//connetc
	struct sockaddr_in clientSockAddr;
	memset(&clientSockAddr, 0, sizeof(clientSockAddr));

	clientSockAddr.sin_family = AF_INET;
	clientSockAddr.sin_port = htons(port);
	clientSockAddr.sin_addr.s_addr = inet_addr(ip);

	if(connect(clientSocket, (struct sockaddr *)&clientSockAddr, sizeof(struct sockaddr)) == -1)
	{
		perror("client connect");
		close(clientSocket);
		exit(1);
	}

	printf("already connected to the server\n");

	return clientSocket;
}

unsigned long fsendBuf(int socket, char *buf, unsigned long size)
{
	unsigned long sendSum = 0;
	while(sendSum < size)
		sendSum += send(socket, buf + sendSum, size - sendSum, 0);

	return sendSum;
}

unsigned long frecvBuf(int socket, char *buf, unsigned long size)
{
	unsigned long recvSum = 0;
	while(recvSum < size)
		recvSum += recv(socket, buf + recvSum, size - recvSum, 0);

	return recvSum;
}
