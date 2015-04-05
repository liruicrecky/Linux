/*************************************************************************
	> File Name: ../src/main/server/redis.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Sun 05 Apr 2015 05:37:36 PM CST
 ************************************************************************/

#include"Redis.h"

#include<iostream>
#include<fstream>

Redis::~Redis()
{
	_connect = NULL;
	_reply = NULL;
}

bool Redis::connect(std::string &ip, int port)
{
	_connect = redisConnect(ip.c_str(), port);

	if(_connect -> err){

		return false;
	}

	std::cout << " -----redis connect success" << std::endl;

	return true;
}

bool Redis::wordExists(std::string &key)
{
	CThreadLockGuard lock(_mutex);
	_reply = (redisReply *)redisCommand(_connect, "EXISTS %s", key.c_str());

	bool flag = _reply -> type;
	freeReplyObject(_reply);

	return flag;
}

std::string Redis::getVal(std::string &key)
{
	CThreadLockGuard lock(_mutex);
	_reply = (redisReply *)redisCommand(_connect, "GET %s", key.c_str());

	std::string val = _reply -> str;
	freeReplyObject(_reply);

	return val;
}

void Redis::setData(std::string &path)
{
	std::ifstream ifs(path.c_str());

	if(!ifs){

		std::cout << "open cache file failed" << std::endl;
		return;
	}

	int pos;
	std::string line;

	while(getline(ifs, line)){

		pos = line.find(' ');
		redisCommand(_connect, "SET %s %s", line.substr(0, pos).c_str(), line.substr(pos + 1).c_str());
	}

	ifs.close();

	std::cout << " -----init redis cache success" << std::endl;
}
