/*************************************************************************
	> File Name: ./include/Thread.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Wed 25 Mar 2015 10:38:52 PM CST
 ************************************************************************/

#ifndef __THREAD_H__
#define __THREAD_H__

#include<pthread.h>
#include<functional>
#include<boost/noncopyable.hpp>

class Thread : boost::noncopyable
{
private:

	pthread_t _threadId;
	bool _isRunning;
	
	static void *runThread(void *);
	std::function<void ()> _callBack;

public:

	explicit Thread(std::function<void ()>);
	~Thread();

public:

	void start();
	void join();

};

#endif
