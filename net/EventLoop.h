#pragma once

#include <vector>
#include <memory>

#include "../base/noncopyable.h"
#include "../base/CurrentThread.h"
#include "../base/Mutex.h"
#include "TimerId.h"
#include "Callbacks.h"

namespace flyhttp 
{
namespace net
{

class Channel;
class Poller;
class TimerQueue;

class EventLoop : noncopyable {
public:

    typedef std::function<void()> Functor;

    EventLoop();
    ~EventLoop();

    void loop();

    void assertInLoopThread() {
        if (!isInLoopThread()) { 
            abortNotInLoopThread(); 
        }
    }

    void quit();

    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);

    bool isInLoopThread() { return threadId_ == CurrentThread::tid(); }

    TimerId runAt(const Timestamp& time, const TimerCallback& cb);
    TimerId runAfter(double delay, const TimerCallback& cb);
    TimerId runInterval(double interval, const TimerCallback& cb);
    
    void runInLoop(Functor cb);
    void queueInLoop(Functor cb);

    static EventLoop* getEventLoopOfCurrentThread();

private:

    void abortNotInLoopThread();
    void handleRead();
    void doPendingFunctors();
    void wakeup();

    typedef std::vector<Channel*> ChannelList;

    bool looping_;
    bool quit_;
    bool callingPendingFunctor_;
    int wakeupFd_;
    const pid_t threadId_;
    ChannelList activeChannels_;
    std::unique_ptr<Poller> poller_;
    std::unique_ptr<TimerQueue> timerQueue_;
    std::unique_ptr<Channel> wakeupChannel_;
    MutexLock mutex_;
    std::vector<Functor> pendingFunctors_;
    Timestamp pollReturnTime_;
};

}
}