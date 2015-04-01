/*************************************************************************
	> File Name: thread.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Sun 29 Mar 2015 10:41:54 PM CST
 ************************************************************************/

#include"Thread.h"
#include<stdio.h>

Thread::Thread(std::function<void ()> callBack) :
	_threadId(0),
	_isRunning(false),
	_callBack(std::move(callBack)) { }

Thread::~Thread()
{
	if(_isRunning)
		pthread_detach(_threadId);
}

void Thread::start()
{
	pthread_create(&_threadId, NULL, runThread, this);
	_isRunning = true;
}

void Thread::join()
{
	if(!_isRunning)
	{
		printf("Thread is not running!\n");
		return;
	}

	pthread_join(_threadId, NULL);
	_isRunning = false;
}

void *Thread::runThread(void *arg)
{
	Thread *pthread = static_cast<Thread *>(arg);
	pthread -> _callBack();
	return NULL;
}

