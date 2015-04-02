/*************************************************************************
	> File Name: threadcache.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Thu 02 Apr 2015 10:39:17 AM CST
 ************************************************************************/

#include"TCache.h"

ThreadCache::ThreadCache() :
	_threadId(0),
	_isRunning(false) { }

ThreadCache::~ThreadCache()
{
	if(_isRunning)
		pthread_detach(_threadId);
}

void ThreadCache::start()
{
	pthread_create(&_threadId, NULL, runThread, this);
	_isRunning = true;
}

void *ThreadCache::runThread(void *arg)
{

	return NULL;
}

