/*************************************************************************
	> File Name: ./include/Cache.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Wed 01 Apr 2015 03:07:06 PM CST
 ************************************************************************/

#ifndef __CACHE_H__
#define __CACHE_H__

#include<string>
#include<tr1/unordered_map>

#include"TLock.h"

class CHasFn
{

public:

	size_t operator()(const std::string &);

};

class CCache
{
	typedef std::tr1::unordered_map<std::string, CHasFn> cacheMap;

private:

	cacheMap _cache;
	CThreadLock _lock;


public:

	CCache(const int &);

public:

	cacheMap::iterator isMapped(const std::string &);
	void writeToFile(std::ostream &);
	void readFromFile(const std::string &);

};

#endif

