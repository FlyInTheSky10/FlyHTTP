cmake_minimum_required(VERSION 3.5)
project(flyhttp)

set(CMAKE_CXX_STANDARD 11)


set(CXX_FLAGS
        -Wall
        -std=c++11
        -lpthread
        -Wno-unused-parameter
        -O3
        )

link_libraries(pthread)

set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O3")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")


set(SOURCE_FILES
        base/CountDownLatch.cpp
        base/CurrentThread.cpp
        base/Thread.cpp
        base/Timestamp.cpp
        base/Exception.cpp
        net/EventLoop.cpp
        net/Channel.cpp
        net/Poller.cpp
        net/TimerQueue.cpp
        net/Timer.cpp
        net/SocketsOps.cpp
        net/EventLoopThread.cpp
        net/Acceptor.cpp
        net/Socket.cpp
        net/InetAddress.cpp
        net/TcpServer.cpp
        net/TcpConnection.cpp
        net/Buffer.cpp
        net/EventLoopThreadPool.cpp
        net/tests/test8.cpp
        )

add_executable(flyhttp  ${SOURCE_FILES})
