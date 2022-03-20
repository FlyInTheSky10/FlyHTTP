#include "../EventLoop.h"
#include "../EventLoopThread.h"
#include <stdio.h>
#include <unistd.h>

void runInThread()
{
  printf("runInThread(): pid = %d, tid = %d\n",
         getpid(), flyhttp::CurrentThread::tid());
}

/*int main()
{
  printf("main(): pid = %d, tid = %d\n",
         getpid(), flyhttp::CurrentThread::tid());

  flyhttp::net::EventLoopThread loopThread(nullptr, "flythread");
  flyhttp::net::EventLoop* loop = loopThread.startLoop();
  loop->runInLoop(runInThread);
  sleep(1);
  loop->runAfter(2, runInThread);
  sleep(3);
  loop->quit();

  printf("exit main().\n");
}*/