#include "../TcpServer.h"
#include "../EventLoop.h"
#include "../InetAddress.h"
#include "../TcpConnection.h"
#include "../../base/Timestamp.h"
#include <stdio.h>
#include <unistd.h>

void onConnection(const flyhttp::net::TcpConnectionPtr& conn)
{
  if (conn->connected())
  {
    printf("onConnection(): new connection [%s] from\n",
           conn->name().c_str());
  }
  else
  {
    printf("onConnection(): connection [%s] is down\n",
           conn->name().c_str());
  }
}

void onMessage(const flyhttp::net::TcpConnectionPtr& conn,
               flyhttp::net::Buffer* buf,
               flyhttp::Timestamp receiveTime)
{
  printf("onMessage(): received %zd bytes from connection [%s] at %s\n",
         buf->readableBytes(),
         conn->name().c_str(),
         receiveTime.toFormattedString().c_str());

  printf("onMessage(): [%s]\n", buf->retrieveAllAsString().c_str());
}

/*int main()
{
  printf("main(): pid = %d\n", getpid());

  flyhttp::net::InetAddress listenAddr(9981);
  flyhttp::net::EventLoop loop;

  flyhttp::net::TcpServer server(&loop, listenAddr, "test6");
  server.setConnectionCallback(onConnection);
  server.setMessageCallback(onMessage);
  server.start();

  loop.loop();
}*/