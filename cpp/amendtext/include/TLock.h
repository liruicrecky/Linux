/*************************************************************************
	> File Name: include/TLock.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Wed 25 Mar 2015 09:44:27 PM CST
 ************************************************************************/

#ifndef __TLOCK_H__
#define __TLOCK_H__

//#include<boost/noncopyable.hpp>
#include<pthread.h>
#include<assert.h>

class CThreadLock 
{
	friend class CThreadCond;
private:

	pthread_mutex_t _mutex;
	bool _isLocked;

//	CThreadLock(const CThreadLock &);
	CThreadLock &operator=(const CThreadLock &);

	void restoreMutexStatus()
	{
		_isLocked = true;
	}
public:

	CThreadLock();
	~CThreadLock();
	bool isLocked() const;
	void Lock();
	void UnLock();
	pthread_mutex_t *getLock();

};

class CThreadLockGuard 
{
private:

	CThreadLock &_mutex;

public:

	CThreadLockGuard(CThreadLock &mutex) : _mutex(mutex)
	{
		_mutex.Lock();
	}
	~CThreadLockGuard()
	{
		_mutex.UnLock();
	}
};

#endif
