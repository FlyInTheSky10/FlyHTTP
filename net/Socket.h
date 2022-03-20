#pragma once

#include "../base/noncopyable.h"

struct tcp_info;

namespace flyhttp
{
namespace net
{

class InetAddress;

class Socket : noncopyable {
public:
    explicit Socket(int sockfd) 
        : sockfd_(sockfd) {}

    ~Socket();

    int fd() const { return sockfd_; }

    bool getTcpInfo(struct tcp_info*) const;
    bool getTcpInfoString(char* buf, int len) const;

    void bindAddress(const InetAddress& localaddr);
    void listen();
    int accept(InetAddress* peeraddr);

    void setReuseAddr(bool on);
    void setReusePort(bool on);

    void shutdownWrite();
    
private:
    const int sockfd_;
};

}
}