/*************************************************************************
  > File Name: ./src/epoll.cpp
  > Author: Reacky
  > Mail:327763224@qq.com 
  > Created Time: Tue 24 Mar 2015 08:21:33 PM CST
 ************************************************************************/

#include"Epoll.h"
#include"SocketIO.h"
#include"CTask.h"

#include<vector>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<iostream>

EPOLL::EPOLL(const int socket)
{
	epollCreate(socket);
}

EPOLL::~EPOLL()
{
	close(_epollFd);
}

int EPOLL::epollCreate(const int socket)
{
	if(-1 == (_epollFd = epoll_create(1024)))
	{
		return -1;
	}

	_socket = socket;

	printf("epoll create success\n");

	return 0;
}

int EPOLL::addToEpoll(const int socket)
{
	memset(&_epollEvent, 0, sizeof(_epollEvent));

	_epollEvent.events = EPOLLIN;
	_epollEvent.data.fd = socket;

	if(-1 == epoll_ctl(_epollFd, EPOLL_CTL_ADD, socket, &_epollEvent))
	{
		perror("epoll");
		return -1;
	}

	printf("add to epoll success\n");

	return 0;
}

int EPOLL::removeFromEpoll(const int Fd)
{
	if(-1 == epoll_ctl(_epollFd, EPOLL_CTL_DEL, Fd, NULL))
		return -1;

	printf("remove from epoll success\n");

	return 0;
}


void EPOLL::isListenEpoll(const int socket, ThreadPool &pool, CConf &conf)
{

	memset(&_returnEpollEvents, 0, sizeof(_returnEpollEvents));

	int readNum = epoll_wait(_epollFd, _returnEpollEvents, 1024, -1);

	char buf[1024];

	//	struct sockaddr_in cliSockAddr[1024];
	struct sockaddr_in tmpCliSockAddr;
	socklen_t cliLen = sizeof(struct sockaddr_in);

	for(int i = 0;i != readNum;++i)
	{
		if(_returnEpollEvents[i].data.fd == socket)
		{
			int cliAccept = accept(_returnEpollEvents[i].data.fd, (struct sockaddr *)&tmpCliSockAddr, &cliLen);
			std::cout << "a new alient online" << std::endl;

			addToEpoll(cliAccept);
		}
		else if(_returnEpollEvents[i].events & EPOLLIN)
		{

			if(0 == read(_returnEpollEvents[i].data.fd, buf, 1024))
			{
				std::cout << "A client offline" << std::endl;
				removeFromEpoll(_returnEpollEvents[i].data.fd);
			}
			else
			{
				buf[strlen(buf) - 1] = '\0'; //notice the buf read from socket has char '\n' from client
				CTask task(conf, buf, _returnEpollEvents[i].data.fd);
				pool.addTask(task);
			}
		}

	}
}
