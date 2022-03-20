#include <cstdio>
#include <unistd.h>

#include "../../base/CurrentThread.h"
#include "../../base/Thread.h"
#include "../EventLoop.h"

flyhttp::net::EventLoop* g_loop;

void threadFunc() {
    printf("threadFunc(): pid = %d, tid = %d\n", 
        getpid(), flyhttp::CurrentThread::tid());
    
    flyhttp::net::EventLoop loop;
    loop.loop();

    g_loop->loop();
}

/*int main() {
    printf("main(): pid = %d, tid = %d\n", 
        getpid(), flyhttp::CurrentThread::tid());
    
    flyhttp::net::EventLoop loop;
    g_loop = &loop;
    loop.loop();

    flyhttp::Thread thread(threadFunc);
    thread.start();

    //flyhttp::net::EventLoop loop2;
    //loop2.loop();

    pthread_exit(NULL); // FIXME

    return 0;
}*/