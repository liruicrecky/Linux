#ifndef MUTEXLOCK_H
#define MUTEXLOCK_H

#include "NonCopyable.h"
//#include <boost/noncopyable.hpp>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//用于pthread系列函数的返回值检查
#define TINY_CHECK(exp) \
    if(!(exp)) \
    {   \
        fprintf(stderr, "File:%s, Line:%d Exp:[" #exp "] is true, abort.\n", __FILE__, __LINE__); abort();\
    }

namespace Tiny
{
class MutexLock : NonCopyable
{
    friend class Condition;
public:
    MutexLock();
    ~MutexLock();
    void lock();
    void unlock();

    bool isLocking() const { return isLocking_; }
    pthread_mutex_t *getMutexPtr() //思考为什么不是const
    { return &mutex_; } 

private:
    void restoreMutexStatus() //提供给Condition的wait使用
    { isLocking_ = true; }


    pthread_mutex_t mutex_;
    bool isLocking_; //是否上锁
};


class MutexLockGuard : NonCopyable
{
public:
    MutexLockGuard(MutexLock &mutex) :mutex_(mutex)
    { mutex_.lock(); }
    ~MutexLockGuard()
    { mutex_.unlock(); }
private:
    MutexLock &mutex_;
};
}

#define MutexLockGuard(m) "Error MutexLockGuard"

#endif //MUTEXLOCK_H