#pragma once

#include <set>
#include <vector>

#include "../base/noncopyable.h"
#include "../base/Timestamp.h"
#include "TimerId.h"
#include "Callbacks.h"
#include "Channel.h"

namespace flyhttp
{
namespace net 
{

class EventLoop;

class TimerQueue : noncopyable {
public:
    TimerQueue(EventLoop* loop);
    ~TimerQueue();

    TimerId addTimer(const TimerCallback& cb,
                    Timestamp when,
                    double interval);

    void addTimerInLoop(Timer* timer);
    
    typedef std::pair<Timestamp, Timer*> Entry;
    typedef std::set<Entry> TimerList;

private:

    void handleRead();

    std::vector<Entry> getExpired(Timestamp now);
    void reset(const std::vector<Entry>& expired, Timestamp now);

    void insert(Timer* timer);

    EventLoop* loop_;
    const int timerfd_;
    Channel timerfdChannel_;
    TimerList timers_;
    bool callingExpiredTimers_;

};

}
}