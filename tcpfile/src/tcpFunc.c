/*************************************************************************
	> File Name: tcpFunc.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Tue 10 Feb 2015 02:35:44 PM CST
 ************************************************************************/

#include"tcp.h"

#define LISTEN_NUM 10

int socketInit(char *ip, int port)
{
	//socket
	int serverSock = socket(AF_INET, SOCK_STREAM, 0);
	if(serverSock == -1){
		perror("socket");
		exit(1);
	}

	//bind
	struct sockaddr_in serverSockAddr;
	memset(&serverSockAddr, 0, sizeof(serverSockAddr));

	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_port = htons(port);
	serverSockAddr.sin_addr.s_addr = inet_addr(ip);

	if(bind(serverSock, (struct sockaddr *)&serverSockAddr, sizeof(struct sockaddr)) == -1){
		perror("bind");
		exit(1);
	}

	//listen
	if(listen(serverSock, LISTEN_NUM) == -1){
		perror("listen");
		exit(1);
	}

	return serverSock;
}

int acceptSocket(int sock)
{
	//accept
	struct sockaddr_in clientSockAddr;
	memset(&clientSockAddr, 0, sizeof(clientSockAddr));

	socklen_t clientSockAddrLen = sizeof(struct sockaddr_in);

	int serverAccept = accept(sock, (struct sockaddr *)&clientSockAddr, &clientSockAddrLen);
	if(serverAccept == -1){
		perror("accept");
		exit(1);
	}

	printf("client: %s : %d has connected server successfully\n", inet_ntoa(clientSockAddr.sin_addr), ntohs(clientSockAddr.sin_port));

	return serverAccept;
}

int connectServer(char *ip, int port)
{
	//socket
	int clientSock = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSock == -1){
		perror("clientsocket");
		exit(1);
	}

	//connect
	struct sockaddr_in clientSockAddr;
	memset(&clientSockAddr, 0, sizeof(clientSockAddr));

	clientSockAddr.sin_family = AF_INET;
	clientSockAddr.sin_port = htons(port);
	clientSockAddr.sin_addr.s_addr = inet_addr(ip);

	if(connect(clientSock, (struct sockaddr *)&clientSockAddr, sizeof(struct sockaddr)) == -1){
		perror("connecct");
		exit(1);
	}

	printf("connected server successfully\n");

	return clientSock;
}

void setNoneBlock(int sfd)
{
	int fileSfd = fcntl(sfd, F_GETFL);
	fileSfd = fileSfd | O_NONBLOCK;
	fcntl(sfd, F_SETFL, fileSfd);
}

unsigned long fsendBuf(int sock, char *buf, unsigned long len)
{
	unsigned long sendSum = 0;
	while(sendSum < len)
		sendSum += send(sock, buf + sendSum, len - sendSum, 0);

	return sendSum;
}

unsigned long frecvBuf(int sock, char *buf, unsigned long len)
{
	unsigned long recvSum = 0;
	while(recvSum < len)
		recvSum += recv(sock, buf + recvSum, len - recvSum, 0);

	return recvSum;
}

unsigned long frecvNonBlock(int sock, char *buf)
{
	unsigned long recvSum = 0;
	unsigned long recvStat;
	while(1)
	{
		recvStat = recv(sock, buf + recvSum, 10240 - recvSum, 0);
		if(recvStat == 0)
		{
			break;
		}
		else if(recvStat > 0)
		{
			recvSum += recvStat;
		}
		else if(recvStat == -1 && errno == EAGAIN)
		{
			return recvSum;
			break;
		}
	}
}

