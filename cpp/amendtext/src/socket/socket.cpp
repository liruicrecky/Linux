/*************************************************************************
	> File Name: ./src/socket.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Thu 26 Mar 2015 04:30:35 PM CST
 ************************************************************************/

#include"Socket.h"
#include<iostream>
#include<stdio.h>

Socket::Socket(const InetAddr &sockAddr, std::string &mode)
{
	_ip = sockAddr.toIp();
	_prot = sockAddr.toPort();

	if(mode == "tcp")
		_type = SOCK_STREAM;
	else if(mode == "udp")
		_type = SOCK_DGRAM;

}

Socket::~Socket()
{
	close(_socket);
}

const void Socket::serInit(const InetAddr &sockAddr)
{
	//socket
	int tSocket = socket(AF_INET, _type, 0);
	if(-1 == tSocket)
	{
		perror("server socket");
		exit(EXIT_FAILURE);
	}

	std::cout << "server socket inited successfully!" << std::endl;

	//bind
	
	if(-1 == bind(tSocket, (struct sockaddr *)sockAddr.getSockAddr(), sizeof(struct sockaddr)))
	{
		perror("server bind");
		exit(EXIT_FAILURE);
	}

	std::cout << "server bind successfully" << std::endl;

	_socket = tSocket;
}

const void Socket::serListen(int number)
{
	if(-1 == listen(_socket, number))
	{
		perror("server listen");
		exit(EXIT_FAILURE);
	}
}

const void Socket::cliInit(const InetAddr &sockAddr)
{
	int tSocket = socket(AF_INET, _type, 0);
	if(-1 == tSocket)
	{
		perror("client socket");
		exit(EXIT_FAILURE);
	}

	_socket = tSocket;
}

const void Socket::cliConnect(const InetAddr &sockAddr)
{
	if(-1 == connect(_socket, (struct sockaddr *)sockAddr.getSockAddr(), sizeof(sockaddr)))
	{
		perror("client connect");
		exit(EXIT_FAILURE);
	}
}
