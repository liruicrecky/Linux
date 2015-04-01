/*************************************************************************
	> File Name: ./include/SocketIO.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Fri 27 Mar 2015 05:24:50 PM CST
 ************************************************************************/

#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__

#include<boost/noncopyable.hpp>
#include<sys/types.h>
#include<Inetaddr.h>

class SocketIO
{

public:

	SocketIO() { }
	~SocketIO() { }

	unsigned long recvFrom(char *, int, const InetAddr &);
	unsigned long sendTo(char *, int, const InetAddr &);

	unsigned long recvBuf(char *, int, unsigned long);
	unsigned long sendBuf(char *, int, unsigned long);

};

#endif
