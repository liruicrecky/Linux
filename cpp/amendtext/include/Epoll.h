/*************************************************************************
	> File Name: ./include/epoll.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Tue 24 Mar 2015 08:21:17 PM CST
 ************************************************************************/

#ifndef __EPOLL_H__
#define __EPOLL_H_

#include"ThreadPool.h"
#include"Conf.h"

#include<boost/noncopyable.hpp>
#include<sys/epoll.h>

class EPOLL : boost::noncopyable
{
private:

	int _epollFd;
	int _socket;
	struct epoll_event _epollEvent;
	struct epoll_event _returnEpollEvents[1024];

	int epollCreate(const int socket);

public:

	EPOLL() { }
	EPOLL(const int socket);
	~EPOLL();

	int addToEpoll(const int);
	int removeFromEpoll(const int);
	void isListenEpoll(const int, ThreadPool &, CConf &);

};


#endif
