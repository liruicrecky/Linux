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

	size_t operator()(const std::string &str)
	{
		size_t hash = 0;
		for(size_t i = 0;i != str.size();++i)
		{
			hash = hash * 31 + str[i];
		}
	
		return hash;
	}

};

class CCache
{
	typedef std::tr1::unordered_map<std::string, std::string, CHasFn> cacheMap;

private:

	cacheMap _cache;
	CThreadLock _lock;

	std::string _cache_path;

public:

	CCache(const std::string &);

public:

	cacheMap::iterator isMapped(const std::string &);
	void addToCache(const std::string &, const std::string &);
	void writeToFile();
	void readFromFile();

	cacheMap *getHashMap() {return &_cache; }

};

#endif

