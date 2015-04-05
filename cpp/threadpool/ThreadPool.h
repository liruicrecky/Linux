#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <boost/noncopyable.hpp>
#include "MutexLock.h"
#include "Condition.h"
#include "Thread.h"
#include <queue>
#include <vector>
#include <functional>
#include <memory>

namespace Tiny
{
class ThreadPool : boost::noncopyable
{
public:
    typedef std::function<void ()> Task;

    ThreadPool(size_t queueSize, size_t threadsNum);

    void start();

    void addTask(Task task); //C++11
    Task getTask();


    void runInThread();

private:
    mutable MutexLock mutex_;
    Condition empty_;
    Condition full_;

    size_t queueSize_;
    std::queue<Task> queue_;

    const size_t threadsNum_;
    std::vector<std::unique_ptr<Thread> > threads_;
    bool isStarted_;
};
}

#endif //THREADPOOL_H