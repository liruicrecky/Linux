/*************************************************************************
	> File Name: ./src/client.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Fri 27 Feb 2015 03:01:34 PM CST
 ************************************************************************/

#include"epoll.h"

int main(int argc, char *argv[])
{
	int clientSocket = clientConnectServer(argv[1], atoi(argv[2]));

	char buf[1024];

	while(memset(buf, 0, 1024), fgets(buf, 1024, stdin) != NULL)
	{
		fsendBuf(clientSocket, buf, 1024);
	}

	close(clientSocket);

	return 0;
}
