/*************************************************************************
	> File Name: ./src/client.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Sat 14 Feb 2015 12:53:49 PM CST
 ************************************************************************/

#include"udp.h"

int main(int argc, char *argv[])
{
	char ip[32];
	int port;

	strcpy(ip, argv[1]);
	port = atoi(argv[2]);

	int fdClient = socket(AF_INET, SOCK_DGRAM, 0);
	if(fdClient == -1)
	{
		perror("socket");
		exit(1);
	}
	
	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr(ip);

	char buf[1024];
	memset(buf, 0, 1024);

	strcpy(buf, "chat?");
	sendto(fdClient, buf, strlen(buf), 0, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr));
	memset(buf, 0, 1024);
	recvfrom(fdClient, buf, 1024, 0, NULL, NULL);

	if(buf[0] == 'Y')
	{
		while(memset(buf, 0, 1024), fgets(buf, 1024, stdin) != NULL)
		{	
			sendto(fdClient, buf, strlen(buf), 0, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr));
			memset(buf, 0, 1024);
			recvfrom(fdClient, buf, 1024, 0, NULL, NULL);
			printf("form %s:%d %s\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port), buf);
		}

		memset(buf, 0, 1024);
		strcpy(buf, "exit");
		sendto(fdClient, buf, strlen(buf), 0, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr));
		close(fdClient);
	}
	else
	{
		close(fdClient);
	}

	return 0;
}
