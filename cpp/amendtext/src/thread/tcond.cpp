/*************************************************************************
	> File Name: ./tcond.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Fri 27 Mar 2015 03:51:06 PM CST
 ************************************************************************/

#include"TCond.h"

//class CThreadCond

CThreadCond::CThreadCond(CThreadLock &mutex) : _mutex(mutex)
{
	pthread_cond_init(&_cond, NULL);
}

CThreadCond::~CThreadCond()
{
	pthread_cond_destroy(&_cond);
}

void CThreadCond::wait()
{
	assert(_mutex.isLocked());
	pthread_cond_wait(&_cond, _mutex.getLock());
	_mutex.restoreMutexStatus();

}

void CThreadCond::notify()
{
	pthread_cond_signal(&_cond);
}

void CThreadCond::broadCast()
{
	pthread_cond_broadcast(&_cond);
}

