/*************************************************************************
	> File Name: threadpool.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Sun 29 Mar 2015 10:55:59 PM CST
 ************************************************************************/

#include"ThreadPool.h"
#include<iostream>

ThreadPool::ThreadPool(size_t threadNum, size_t queueSize) : 
	_queueSize(queueSize),
	_isStarting(false),
	_threadNum(threadNum),
	_empty(_mutex),
	_full(_mutex)  {  }

void ThreadPool::start()
{
	_isStarting = true;

	for(size_t i = 0;i != _threadNum;++i)
	{
		_threads.push_back(std::unique_ptr<Thread>(new Thread(std::bind(&ThreadPool::runThread, this))));
	}

	for(size_t i = 0;i != _threadNum;++i)
	{
		_threads[i] -> start();
	}
}

void ThreadPool::addTask(CTask task)
{
	CThreadLockGuard lock(_mutex);
	while(_queue.size() >= _queueSize)
		_full.wait();

	//_queue.push(std::move(task));
	_queue.push(task);
	_full.notify();
}

CTask ThreadPool::getTask()
{
	CThreadLockGuard lock(_mutex);
	while(_queue.empty())
		_full.wait();

	CTask task = _queue.front();
	_queue.pop();
	_empty.notify();
	return task;
}

void ThreadPool::runThread()
{
	while(1)
	{
		CTask task(getTask());
		task.execute();
	}
}

