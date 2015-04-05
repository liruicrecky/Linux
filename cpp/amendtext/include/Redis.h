/*************************************************************************
	> File Name: Redis.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Sun 05 Apr 2015 05:34:54 PM CST
 ************************************************************************/

#ifndef __REDIS_H__
#define __REDIS_H__

#include"TLock.h"

#include<string>
#include<boost/noncopyable.hpp>
#include<hiredis/hiredis.h>

class Redis : boost::noncopyable
{

private:

	redisContext *_connect;
	redisReply *_reply;

	mutable CThreadLock _mutex;

public:

	Redis() { }
	~Redis();

	bool connect(std::string &, int );
	std::string getError() {return _connect -> errstr; }

	bool wordExists(std::string &);
	std::string getVal(std::string &);

	void setData(std::string &);
	void setNewData(std::string &, std::string &);

};

#endif
