/*************************************************************************
	> File Name: ./include/Inetaddr.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Fri 27 Mar 2015 10:36:43 AM CST
 ************************************************************************/

#ifndef __INETADDR_H__
#define __INETADDR_H__

#include<string>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

class InetAddr
{
private:
	
	struct sockaddr_in _sockAddr;

public:

	explicit InetAddr(int);
	InetAddr(const std::string &, int);
	InetAddr(const struct sockaddr_in &);

	void setSockAddr(const struct sockaddr_in &);
	const struct sockaddr_in *getSockAddr() const;

	std::string toIp() const;
	int toPort() const;
	
};

#endif

