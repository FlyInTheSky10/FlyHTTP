#pragma once

#include "../base/noncopyable.h"
#include "InetAddress.h"
#include "Channel.h"
#include "Socket.h"

namespace flyhttp
{
namespace net
{

class EventLoop;

class Acceptor : noncopyable {
public:
    typedef std::function<void (int sockfd, const InetAddress&)> NewConnectionCallback;

    Acceptor(EventLoop* loop, const InetAddress listenAddr);

    void setNewConnectionCallback(const NewConnectionCallback& cb) { newConnectionCallback_ = cb; }

    bool listenning() const { return listenning_; }
    void listen();

private:
    void handleRead();
    
    EventLoop* loop_;
    Socket acceptSocket_;
    Channel acceptChannel_;
    NewConnectionCallback newConnectionCallback_;
    bool listenning_;
};

}
}