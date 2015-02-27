/*************************************************************************
	> File Name: ./src/client.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Tue 24 Feb 2015 12:41:45 PM CST
 ************************************************************************/

#include"gobang.h"

int main(int argc, char *argv[])
{
	char ip[32];
	int port;

	strcpy(ip, argv[1]);
	port = atoi(argv[2]);

	//udp init socket
	
	int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if(clientSocket == -1)
	{
		perror("socket");
		exit(1);
	}

	//udp send to server
	
	struct sockaddr_in serverSockAddr;
	memset(&serverSockAddr, 0, sizeof(serverSockAddr));

	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_port = htons(port);
	serverSockAddr.sin_addr.s_addr = inet_addr(ip);
	int serverSockAddrSize = sizeof(struct sockaddr);

	char buf[32];
	memset(buf, 0, sizeof(buf));

	char clientColor;
	printf("please select the color,(1 for white,2 for black)");
	scanf("%c", &clientColor);
	
	//send color to server
	
	sendto(clientSocket, &clientColor, sizeof(clientColor), 0, (struct sockaddr *)&serverSockAddr, sizeof(struct sockaddr));

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

	int flag = 0, firstGet = 0;
	int x, y;
	while(memset(buf, 0, sizeof(buf)))
	{
		if(flag == 0)
		{
			recvfrom(clientSocket, buf, sizeof(buf), 0, (struct sockaddr *)&serverSockAddr, &serverSockAddrSize);
			sscanf(buf, "%d %d", &x, &y);
			--x;
			--y;
			chessesPad[x][y] = serverColor;
			refreshChessesPad(pchPad);
			if(checkWin(pchPad, serverColor))
			{
				printf("you lose the game\n");
				close(clientSocket);
				break;
			}
			flag = 1;
		}
		memset(buf, 0, sizeof(buf));
		if(firstGet == 0)
		{
			fgetc(stdin);
			firstGet = 1;
		}
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
		else if(chessesPad[x][y] != '0')
		{
			printf("aleady exist! find another place!\n");
			continue;
		}
		else
		{
			sendto(clientSocket, buf, sizeof(buf), 0, (struct sockaddr *)&serverSockAddr, sizeof(struct sockaddr));
			flag = 0;
			chessesPad[x][y] = clientColor;
			refreshChessesPad(pchPad);
			if(checkWin(pchPad, clientColor))
			{
				printf("you win the game!\n");
				close(clientSocket);
				break;
			}
		}
	}

	return 0;
}
