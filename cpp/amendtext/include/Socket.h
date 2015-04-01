/*************************************************************************
	> File Name: ./include/Socket.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Thu 26 Mar 2015 04:30:49 PM CST
 ************************************************************************/

#ifndef __SOCKET_H__
#define __SOCKET_H__

#include<boost/noncopyable.hpp>
#include"Inetaddr.h"
#include<unistd.h>

class Socket : boost::noncopyable
{
private:

	int _socket;
	int _prot;
	int _type;
	std::string _ip;

public:

	Socket(const InetAddr &, std::string &);
	~Socket();

	int getSocket() const
	{
		return _socket;
	}
	const void serInit(const InetAddr &);
	const void serListen(int);
	const void cliInit(const InetAddr &);
	const void cliConnect(const InetAddr &);
};


#endif
