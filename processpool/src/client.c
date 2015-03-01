/*************************************************************************
	> File Name: ./src/client.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Sun 01 Mar 2015 09:36:39 PM CST
 ************************************************************************/

#include"processpool.h"

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
	memset(buf, 0, sizeof(buf));
	recv(clientSocket, buf, 1024, 0);
	printf("from server:%s\n", buf);

	while(memset(buf, 0, 1024), fgets(buf, 1024, stdin) != NULL)
	{
		send(clientSocket, buf, strlen(buf), 0);
		if(buf[0] == 'q')
			break;
	}

	close(clientSocket);

	return 0;
}
