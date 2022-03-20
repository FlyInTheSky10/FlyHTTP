#pragma once

#include "../base/noncopyable.h"
#include "../base/Atomic.h"
#include "InetAddress.h"
#include "Acceptor.h"
#include "Callbacks.h"

#include <map>

namespace flyhttp
{
namespace net
{

class EventLoop;
class EventLoopThreadPool;

class TcpServer : noncopyable {
public:
    typedef std::function<void(EventLoop*)> ThreadInitCallback;

    TcpServer(EventLoop* loop, const InetAddress& listenAddr,  const std::string nameArg);
    ~TcpServer();

    /// Not thread safe.
    void setConnectionCallback(const ConnectionCallback& cb) { connectionCallback_ = cb; }
    void setMessageCallback(const MessageCallback& cb) { messageCallback_ = cb; }

    void removeConnection(const TcpConnectionPtr& conn);
    void removeConnectionInLoop(const TcpConnectionPtr& conn);

    void start();

    void setThreadNum(int numThreads);
    void setThreadInitCallback(const ThreadInitCallback& cb) { threadInitCallback_ = cb; }
    // valid after calling start()
    std::shared_ptr<EventLoopThreadPool> threadPool() { return threadPool_; }

private:
    void newConnection(int sockfd, const InetAddress& peerAddr);

    typedef std::map<std::string, TcpConnectionPtr> ConnectionMap;

    EventLoop* loop_;
    const std::string name_;
    std::unique_ptr<Acceptor> acceptor_;
    std::shared_ptr<EventLoopThreadPool> threadPool_;
    ConnectionCallback connectionCallback_;
    MessageCallback messageCallback_;
    ThreadInitCallback threadInitCallback_;
    AtomicInt32 started_;
    int nextConnId_;
    ConnectionMap connections_;
};

}
}