/*************************************************************************
	> File Name: ./src/tlock.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Wed 25 Mar 2015 09:49:04 PM CST
 ************************************************************************/

#include"TLock.h"
#include<assert.h>

//class CThreadLock

CThreadLock::CThreadLock()
{
	_isLocked = false;
	pthread_mutex_init(&_mutex, NULL);
}

CThreadLock::~CThreadLock()
{
	assert(!isLocked());

	pthread_mutex_destroy(&_mutex);
}

bool CThreadLock::isLocked() const
{
	return _isLocked;
}

void CThreadLock::Lock()
{
	pthread_mutex_lock(&_mutex);
	_isLocked = true;
}

void CThreadLock::UnLock()
{
	pthread_mutex_unlock(&_mutex);
	_isLocked = false;
}

pthread_mutex_t *CThreadLock::getLock()
{
	return &_mutex;
}

