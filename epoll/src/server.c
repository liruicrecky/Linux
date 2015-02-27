/*************************************************************************
	> File Name: ./src/server.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Fri 27 Feb 2015 11:08:54 AM CST
 ************************************************************************/

#include"epoll.h"
#define EPOLL_SIZE 1024

int main(int argc, char *argv[])
{
	int serverSocket = initServerSocket(argv[1], atoi(argv[2]));
	
	//epoll
	
	int epoll_fd = epoll_create(EPOLL_SIZE);
	if(epoll_fd == -1)
	{
		perror("epoll");
		exit(1);
	}

	struct epoll_event serverEpollEvent, clientEpollEvent[1024];
	memset(&serverEpollEvent, 0, sizeof(serverEpollEvent));

	serverEpollEvent.events = EPOLLIN;
	serverEpollEvent.data.fd = serverSocket;

	if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, serverSocket, &serverEpollEvent) == -1)
	{
		perror("epoll_ctl");
		close(epoll_fd);
		exit(1);
	}

	char buf[1024];
	int readableEvents;
	int cnt;
	int clientAccept;

	while(1)
	{
		memset(&clientEpollEvent, 0, sizeof(clientEpollEvent));
		readableEvents = epoll_wait(epoll_fd, clientEpollEvent, 1024, -1);
		for(cnt = 0;cnt < readableEvents;cnt ++)
		{
			if(clientEpollEvent[cnt].events & EPOLLIN && clientEpollEvent[cnt].data.fd == serverSocket)
			{
				clientAccept = accept(clientEpollEvent[cnt].data.fd, NULL, NULL);
				printf("a new client online!\n");

				memset(&serverEpollEvent, 0, sizeof(serverEpollEvent));
				serverEpollEvent.events = EPOLLIN;
				serverEpollEvent.data.fd = clientAccept;

				if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, clientAccept, &serverEpollEvent) == -1)
				{
					perror("client epoll_ctl");
					close(epoll_fd);
					exit(1);
				}
				

			}
			else if(clientEpollEvent[cnt].events & EPOLLIN)
			{
				memset(buf, 0, 1024);
				if(frecvBuf(clientEpollEvent[cnt].data.fd, buf, 1024) == 0)
				{
					printf("a client exit\n");
					epoll_ctl(epoll_fd, EPOLL_CTL_DEL, clientEpollEvent[cnt].data.fd, NULL);
				}
				else
				{
					printf("client says:%s", buf);
				}
			}
		}
	}
	
	close(epoll_fd);
	close(serverSocket);

	return 0;
}

