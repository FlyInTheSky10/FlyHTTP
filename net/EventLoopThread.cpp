#include "EventLoopThread.h"
#include "EventLoop.h"

using namespace flyhttp;
using namespace net;

EventLoopThread::EventLoopThread(const ThreadInitCallback& cb, const string name)
    : exiting_(false),
      loop_(nullptr),
      mutex_(),
      cond_(mutex_),
      thread_(std::bind(&EventLoopThread::threadFunc, this), name),
      callback_(cb) {

}

EventLoopThread::~EventLoopThread() {
    exiting_ = true;
    if (loop_ != nullptr) {
        loop_->quit();
        thread_.join();
    }
}

EventLoop* EventLoopThread::startLoop() {
    assert(!thread_.started());
    thread_.start();

    {
        MutexLockGuard lock(mutex_);
        while (loop_ == NULL) {
            cond_.wait();
        }
    }

    return loop_;
}

void EventLoopThread::threadFunc() {
    EventLoop loop;

    if (callback_) {
        callback_(&loop);
    }

    {
        MutexLockGuard lock(mutex_);
        loop_ = &loop;
        cond_.notify();
    }
    loop.loop();

    MutexLockGuard lock(mutex_);
    loop_ = nullptr;
}