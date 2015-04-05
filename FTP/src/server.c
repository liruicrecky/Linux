/*************************************************************************
	> File Name: ./src/main.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Sat 28 Feb 2015 08:27:39 PM CST
 ************************************************************************/

#include"ftp.h"
#define LISTEN_NUM 10

int main(int argc, char *argv[])
{
	signal(17, recvFork);
	if(argc < 3)
	{
		printf("argv error\n");
		exit(1);
	}

	pCHILD pChi = (pCHILD)calloc(1, sizeof(CHILD));
	makeChild(pChi, atoi(argv[3]));

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
	serverSockAddr.sin_port = htons(atoi(argv[2]));
	serverSockAddr.sin_addr.s_addr = inet_addr(argv[1]);

	if(bind(serverSocket, (struct sockaddr *)&serverSockAddr, sizeof(struct sockaddr)) == -1)
	{
		perror("bind");
		close(serverSocket);
		exit(1);
	}

	//listen
	
	if(listen(serverSocket, LISTEN_NUM) == -1)
	{		
		perror("listen");
		close(serverSocket);
		exit(1);
	}

	//epoll create
	
	int serverEpoll = epoll_create(1024);

	if(serverEpoll == -1)
	{
		perror("epoll");
		close(serverSocket);
		exit(1);
	}

	//epoll add
	struct epoll_event serEpollEvent, processEpollEvents[atoi(argv[3])], waitEpollEvents[1024];
	memset(&serEpollEvent, 0, sizeof(serEpollEvent));
	memset(&processEpollEvents, 0, sizeof(processEpollEvents));

	//add server socket
	
	serEpollEvent.events = EPOLLIN;
	serEpollEvent.data.fd = serverSocket;
	
	if(epoll_ctl(serverEpoll, EPOLL_CTL_ADD, serverSocket, &serEpollEvent) == -1)
	{
		perror("server epoll");
		close(serverSocket);
		close(serverEpoll);
		exit(1);
	}

	//add process 

	int index;

	for(index = 0;index < atoi(argv[3]);index++)
	{
		processEpollEvents[index].events = EPOLLIN;
		processEpollEvents[index].data.fd = pChi[index].socketFd;
	}

	for(index = 0;index < atoi(argv[3]);index++)
	{
		if(epoll_ctl(serverEpoll, EPOLL_CTL_ADD, pChi[index].socketFd, &processEpollEvents[index]) == -1)
		{
			perror("process epoll");
			close(serverSocket);
			close(serverEpoll);
			exit(1);
		}
	}

	//accept
	
	int readableEpoll;
	int cnt;
	int clientAccept;
	char buf[1024];
	pid_t pid;
	
	while(1)
	{
		memset(&waitEpollEvents, 0, sizeof(waitEpollEvents));
		readableEpoll = epoll_wait(serverEpoll, waitEpollEvents, 1024, -1);
		for(cnt = 0;cnt < readableEpoll;cnt++)
		{
			if(waitEpollEvents[cnt].events & EPOLLIN && waitEpollEvents[cnt].data.fd == serverSocket)
			{
				clientAccept = accept(waitEpollEvents[cnt].data.fd, NULL, NULL);
				printf("a new client online!\n");
				
				for(index = 0;index < atoi(argv[3]);index++)
				{
					if(pChi[index].stat == FREE)
						break;
				}
				if(index == atoi(argv[3]))
				{
					printf("full client!\n");
					continue;
				}
				sendFd(pChi[index].socketFd, clientAccept);
				pChi[index].stat = BUSY;
			}
			else if(waitEpollEvents[cnt].events & EPOLLIN && waitEpollEvents[cnt].data.fd != serverSocket)
			{

					
				memset(buf, 0, 1024);
				read(waitEpollEvents[cnt].data.fd, buf, 1024);
				sscanf(buf, "%u", &pid);
				for(index = 0;index < atoi(argv[3]);index++)
				{
					if(pChi[index].childPid == pid)
					{
				epoll_ctl(serverEpoll, EPOLL_CTL_DEL, pChi[index].socketFd, &processEpollEvents[index]);
						break;
					}
				}
				
				printf("A client is offline\n");
			}
		}
	
	}

	return 0;
}

