/*************************************************************************
	> File Name: ./src/udp.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Sat 14 Feb 2015 12:23:25 PM CST
 ************************************************************************/

#include"udp.h"

int socketInit(char *ip, int port)
{
	//socket
	int serSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if(serSocket == -1)
	{
		perror("init socket");
		exit(1);
	}

	//bind
	struct sockaddr_in serSockAddr;
	memset(&serSockAddr, 0, sizeof(serSockAddr));

	serSockAddr.sin_family = AF_INET;
	serSockAddr.sin_port = htons(port);
	serSockAddr.sin_addr.s_addr = inet_addr(ip);

	if(bind(serSocket, (struct sockaddr *)&serSockAddr, sizeof(struct sockaddr)) == -1)
	{
		perror("bind");
		close(serSocket);
		exit(1);
	}

	return serSocket;
}
