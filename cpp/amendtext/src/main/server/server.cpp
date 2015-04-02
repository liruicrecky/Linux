/*************************************************************************
  > File Name: src/main.cpp
  > Author: Reacky
  > Mail:327763224@qq.com 
  > Created Time: Fri 27 Mar 2015 04:28:54 PM CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<string.h>

#include"Conf.h"
#include"Inetaddr.h"
#include"Socket.h"
#include"SocketIO.h"
#include"Epoll.h"
#include"ThreadPool.h"


int main(int argc, char **argv)
{	

	//init conf file
	CConf conf(argv[1]);

	//init threadpool
	std::string path = conf.getCachePath();
	ThreadPool pool(conf.ThreadNum(), conf.QueueSize(), path);
	pool.start();

	//init socket
	std::string mode = conf.Mode(); //need to fix

	InetAddr serSocketAddr(conf.Ip(), conf.Port()); 
	Socket serSocket(serSocketAddr, mode);  //here
	serSocket.serInit(serSocketAddr);
	serSocket.serListen(10);

	SocketIO serSocketIO;

	//epoll init
	EPOLL serEpoll(serSocket.getSocket());
	serEpoll.addToEpoll(serSocket.getSocket());

	std::cout << std::endl << "SERVER START SUCCESS" << std::endl;

	while(1)
	{
		serEpoll.isListenEpoll(serSocket.getSocket(), pool, conf);
	}

	return 0;
}
