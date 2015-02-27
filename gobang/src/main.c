/*************************************************************************
	> File Name: ./src/main.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Mon 23 Feb 2015 02:08:00 PM CST
 ************************************************************************/

#include"gobang.h"

int main(int argc, char *argv[])
{
	char ip[32];
	int port;

	strcpy(ip, argv[1]);
	port = atoi(argv[2]);

	//udp init server socket
	
	int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if(serverSocket == -1)
	{
		perror("socket");
		exit(1);
	}

	//udp bind
	
	struct sockaddr_in serverSocketAddr;
	memset(&serverSocketAddr, 0, sizeof(serverSocketAddr));

	serverSocketAddr.sin_family = AF_INET;
	serverSocketAddr.sin_port = htons(port);
	serverSocketAddr.sin_addr.s_addr = inet_addr(ip);

	if(bind(serverSocket, (struct sockaddr *)&serverSocketAddr, sizeof(struct sockaddr)) == -1)
	{
		perror("bind");
		close(serverSocket);
		exit(1);
	}

	//recvform client get information
	char buf[32];
	char clientColor;
	memset(buf, 0, sizeof(buf));

	struct sockaddr_in clientSockAddr;
	memset(&clientSockAddr, 0, sizeof(clientSockAddr));
	int clientSockAddrSize = sizeof(struct sockaddr);

	if(recvfrom(serverSocket, buf, sizeof(buf), 0, (struct sockaddr *)&clientSockAddr, &clientSockAddrSize) == -1)
	{
		perror("recvfrom client");
		close(serverSocket);
		exit(1);
	}

	clientColor = buf[0];

	//chesses 
	
	char serverColor;
	if(clientColor == '1')
		serverColor = '2';
	else
		serverColor = '1';
		
	char chessesPad[15][15];
	memset(chessesPad, '0', sizeof(char) * 225);
	char *pchPad = (char *)chessesPad;
	refreshChessesPad(pchPad);


	int flag = 1;
	int x, y;
	while(memset(buf, 0, sizeof(buf)))
	{
		if(flag == 0)
		{
			recvfrom(serverSocket, buf, sizeof(buf), 0, (struct sockaddr *)&clientSockAddr, &clientSockAddrSize);
			sscanf(buf, "%d %d", &x, &y);
			--x;
			--y;
			chessesPad[x][y] = clientColor;
			refreshChessesPad(pchPad);
			if(checkWin(pchPad, clientColor))
			{
				printf("you lose the game\n");
				close(serverSocket);
				break;
			}
			flag = 1;
		}
		memset(buf, 0, sizeof(buf));
		fflush(stdin);
		fgets(buf, sizeof(buf), stdin);
		sscanf(buf, "%d %d", &x, &y);
		--x;
		--y;
		if(x > 14 || x < 0 || y > 14 || y < 0)
		{
			printf("invalid num!\n");
			continue;
		}
		else if(chessesPad[x][y] != '0')
		{
			printf("aleady exist! find another place!\n");
			continue;
		}
		else
		{
			sendto(serverSocket, buf, sizeof(buf), 0, (struct sockaddr *)&clientSockAddr, sizeof(struct sockaddr));
			flag = 0;
			chessesPad[x][y] = serverColor;
			refreshChessesPad(pchPad);
			if(checkWin(pchPad, serverColor))
			{
				printf("you win the game!\n");
				close(serverSocket);
				break;
			}
		}
	}
	
	
	return 0;
}

