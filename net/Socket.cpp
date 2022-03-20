#include "Socket.h"
#include "SocketsOps.h"
#include "InetAddress.h"

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <iostream>

using namespace flyhttp;
using namespace net;

Socket::~Socket() {
  sockets::close(sockfd_);
}

bool Socket::getTcpInfo(struct tcp_info* tcpi) const {
  socklen_t len = sizeof(*tcpi);
  memZero(tcpi, len);
  return ::getsockopt(sockfd_, SOL_TCP, TCP_INFO, tcpi, &len) == 0;
}

void Socket::bindAddress(const InetAddress& addr) {
  sockets::bind(sockfd_, addr.getSockAddr());
}

void Socket::listen() {
  sockets::listen(sockfd_);
}

int Socket::accept(InetAddress* peeraddr) {
  struct sockaddr_in6 addr;
  memZero(&addr, sizeof addr);
  int connfd = sockets::accept(sockfd_, &addr);
  if (connfd >= 0) {
    peeraddr->setSockAddrInet6(addr);
  }
  return connfd;
}

void Socket::setReuseAddr(bool on) {
  int optval = on ? 1 : 0;
  ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR,
               &optval, static_cast<socklen_t>(sizeof optval));
}

void Socket::setReusePort(bool on) {
  int optval = on ? 1 : 0;
  int ret = ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT,
                         &optval, static_cast<socklen_t>(sizeof optval));
  if (ret < 0 && on) {
    std::cout << "SO_REUSEPORT failed." << std::endl;
  }
}

void Socket::shutdownWrite() {
  sockets::shutdownWrite(sockfd_);
}