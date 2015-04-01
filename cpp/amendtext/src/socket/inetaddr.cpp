/*************************************************************************
	> File Name: src/inetaddr.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Fri 27 Mar 2015 10:36:34 AM CST
 ************************************************************************/

#include"Inetaddr.h"

InetAddr::InetAddr(int port)
{
	memset(&_sockAddr, 0, sizeof(_sockAddr));
	_sockAddr.sin_family = AF_INET;
	_sockAddr.sin_port = htons(port);
	_sockAddr.sin_addr.s_addr = INADDR_ANY;
}

InetAddr::InetAddr(const std::string &ip, int port)
{
	memset(&_sockAddr, 0, sizeof(_sockAddr));
	_sockAddr.sin_family = AF_INET;
	_sockAddr.sin_port = htons(port);
	_sockAddr.sin_addr.s_addr = inet_addr(ip.c_str());
}

InetAddr::InetAddr(const struct sockaddr_in &sockAddr)
{
	memset(&_sockAddr, 0, sizeof(_sockAddr));
	_sockAddr = sockAddr;
}

void InetAddr::setSockAddr(const struct sockaddr_in &sockAddr)
{
	memset(&_sockAddr, 0, sizeof(_sockAddr));
	_sockAddr = sockAddr;	
}

const struct sockaddr_in *InetAddr::getSockAddr() const
{
	return &_sockAddr;
}

std::string InetAddr::toIp() const
{
	return inet_ntoa(_sockAddr.sin_addr);
}

int InetAddr::toPort() const
{
	return ntohs(_sockAddr.sin_port);
}
