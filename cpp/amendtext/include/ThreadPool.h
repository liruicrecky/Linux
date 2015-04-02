/*************************************************************************
	> File Name: /home/liruicheng/LinuxCode/cpp/amendtext/include/ThreadPool.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Sun 29 Mar 2015 10:56:26 PM CST
 ************************************************************************/

#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include"Thread.h"
#include"TLock.h"
#include"TCond.h"
#include"CTask.h"
#include"Cache.h"

#include<queue>
#include<vector>
#include<memory>
#include<functional>
#include<boost/noncopyable.hpp>

class ThreadPool : boost::noncopyable
{

private:

	std::queue<CTask> _queue;
	std::vector<std::unique_ptr<Thread> > _threads;

	size_t _queueSize;
	bool _isStarting;

	const size_t _threadNum;

	CThreadCond _empty;
	CThreadCond _full;
	mutable CThreadLock _mutex;

	CCache _cache;

public:

	ThreadPool(size_t, size_t, std::string &);

public:

	void start();

	void addTask(CTask);
	CTask getTask();

	void runThread();

};

#endif
