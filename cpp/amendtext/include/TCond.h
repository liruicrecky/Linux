/*************************************************************************
	> File Name: ./TCond.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Fri 27 Mar 2015 03:47:45 PM CST
 ************************************************************************/

#ifndef __TCOND_H__
#define __TCOND_H__

#include"TLock.h"

class CThreadCond
{
private:

	CThreadLock &_mutex;
	pthread_cond_t _cond;

//	CThreadCond(const CThreadCond &);
	CThreadCond &operator=(const CThreadCond &);

public:

	CThreadCond(CThreadLock &);
	~CThreadCond();
	void wait();
	void notify();
	void broadCast();
};

#endif
