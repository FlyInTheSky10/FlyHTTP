#include "../TcpServer.h"
#include "../EventLoop.h"
#include "../InetAddress.h"
#include "../TcpConnection.h"
#include <stdio.h>
#include <unistd.h>

using namespace flyhttp;
using namespace net;

void onConnection(const TcpConnectionPtr& conn)
{
  if (conn->connected())
  {
    printf("onConnection(): tid=%d new connection [%s] from \n",
           CurrentThread::tid(),
           conn->name().c_str());
  }
  else
  {
    printf("onConnection(): tid=%d connection [%s] is down\n",
           CurrentThread::tid(),
           conn->name().c_str());
  }
}

void onMessage(const TcpConnectionPtr& conn,
               Buffer* buf,
               Timestamp receiveTime)
{
  printf("onMessage(): tid=%d received %zd bytes from connection [%s] at %s\n",
         CurrentThread::tid(),
         buf->readableBytes(),
         conn->name().c_str(),
         receiveTime.toFormattedString().c_str());

  printf("onMessage(): [%s]\n", buf->retrieveAllAsString().c_str());
}

int main(int argc, char* argv[])
{
  printf("main(): pid = %d\n", getpid());

  InetAddress listenAddr(9981);
  EventLoop loop;

  TcpServer server(&loop, listenAddr, "flyServer");
  server.setConnectionCallback(onConnection);
  server.setMessageCallback(onMessage);
  server.setThreadNum(10);
  server.start();

  loop.loop();
}