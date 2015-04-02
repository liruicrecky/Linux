/*************************************************************************
	> File Name: /home/liruicheng/LinuxCode/cpp/amendtext/include/TCache.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Thu 02 Apr 2015 10:39:43 AM CST
 ************************************************************************/

#ifndef __TCACHE_H__
#define __TCACHE_H__

#include<pthread.h>

#include<vector>
#include<memory>
#include<boost/noncopyable.hpp>

#include"Thread.h"

class ThreadCache : boost::noncopyable
{

private:

	pthread_t _threadId;
	std::vector<std::unique_ptr<Thread> > *_threads;
	bool _isRunning;

	static void *runThread(void *);

public:

	ThreadCache();
	~ThreadCache();

public:

	void start();
	void setVecThread();

};

#endif
