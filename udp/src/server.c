/*************************************************************************
	> File Name: ./src/server.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Sat 14 Feb 2015 12:20:00 PM CST
 ************************************************************************/

#include"udp.h"

int main(int argc, char *argv[])
{
	char ip[32];
	int port;

	strcpy(ip, argv[1]);
	port = atoi(argv[2]);

	int fdServer = socketInit(ip, port);

	struct sockaddr_in clientAddr;
	socklen_t clientSockLen = sizeof(clientAddr);

	char buf[1024];
	memset(buf, 0, 1024);

	recvfrom(fdServer, buf, 1024, 0, (struct sockaddr *)&clientAddr, &clientSockLen);
	printf("%s:%d msg: %s\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), buf);

	printf("Y | N ?\n");
	memset(buf, 0, 1024);
	fgets(buf, 1024, stdin);

	sendto(fdServer, buf, strlen(buf), 0, (struct sockaddr *)&clientAddr, sizeof(struct sockaddr));

	if(buf[0] == 'Y')
	{
		while(memset(buf, 0, 1024), recvfrom(fdServer, buf, 1024, 0, (struct sockaddr *)&clientAddr, &clientSockLen))
		{
			printf("form %s:%d : %s\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), buf);

			if(strcmp(buf, "exit") == 0)
			{
				close(fdServer);
				break;
			}

			memset(buf, 0, 1024);
			fgets(buf, 1024, stdin);
			sendto(fdServer, buf, strlen(buf), 0, (struct sockaddr *)&clientAddr, sizeof(struct sockaddr));
		}
	}
	else
	{
		close(fdServer);
	}

	return 0;
}

