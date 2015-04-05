/*************************************************************************
	> File Name: ./src/socketio.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Fri 27 Mar 2015 05:25:03 PM CST
 ************************************************************************/

#include"SocketIO.h"
#include<sys/socket.h>

unsigned long SocketIO::recvFrom(char *buf, int socket, const InetAddr &sockAddr)
{
	socklen_t sockAddrLen = sizeof(struct sockaddr);
	unsigned long size = recvfrom(socket, buf, sizeof(buf), 0, (struct sockaddr *)sockAddr.getSockAddr(), &sockAddrLen);

	return size;
}

unsigned long SocketIO::sendTo(char *buf, int socket, const InetAddr &sockAddr)
{
	unsigned long size = sendto(socket, buf, sizeof(buf), 0, (struct sockaddr *)sockAddr.getSockAddr(), sizeof(struct sockaddr));

	return size;
}

unsigned long SocketIO::sendBuf(char *buf, int socket, unsigned long size)
{
	unsigned long sendSum = 0;
	while(sendSum < size)
	{
		sendSum += send(socket, buf + sendSum, size - sendSum, 0);
	}

	return sendSum;
}

unsigned long SocketIO::recvBuf(char *buf, int socket, unsigned long size)
{
	unsigned long recvSum = 0;
	while(recvSum < size)
	{
		recvSum += recv(socket, buf + recvSum, size - recvSum, 0);
	}

	return recvSum;
}

