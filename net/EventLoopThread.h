#pragma once

#include "../base/Mutex.h"
#include "../base/Condition.h"
#include "../base/Thread.h"

namespace flyhttp
{
namespace net
{

class EventLoop;

class EventLoopThread {
public:

    typedef std::function<void(EventLoop*)> ThreadInitCallback;

    EventLoopThread(const ThreadInitCallback& cb, const string name);
    ~EventLoopThread();

    EventLoop* startLoop();
    void threadFunc();

private:
    bool exiting_;
    EventLoop* loop_;
    MutexLock mutex_;
    Condition cond_;
    Thread thread_;
    ThreadInitCallback callback_;
};

}
}