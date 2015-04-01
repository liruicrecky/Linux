/*************************************************************************
	> File Name: ./src/client.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Fri 27 Mar 2015 11:06:07 PM CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<string.h>
#include<stdio.h>

#include"Inetaddr.h"
#include"Socket.h"
#include"SocketIO.h"


int main(int argc, char **argv)
{
	std::string ip(argv[1]);
	int port = atoi(argv[2]);
	std::string mode("tcp"); 

	//addr
	InetAddr cliSocketAddr(ip, port);
	//socket info save
	Socket cliSocket(cliSocketAddr, mode);
	//socket init
	cliSocket.cliInit(cliSocketAddr);
	cliSocket.cliConnect(cliSocketAddr);

	SocketIO cliSocketIO;

	char buf[1024];
	struct sockaddr_in tmp;

	while(memset(buf, 0, sizeof(buf)), fgets(buf, 1024, stdin) != NULL)
	{	
		cliSocketIO.sendBuf(buf, cliSocket.getSocket(), 1024);
		cliSocketIO.recvBuf(buf, cliSocket.getSocket(), 1024);
		std::cout << buf << std::endl;
	}
}
