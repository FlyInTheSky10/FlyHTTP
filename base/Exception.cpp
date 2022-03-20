#include "Exception.h"
#include "CurrentThread.h"

namespace flyhttp
{

Exception::Exception(string msg)
  : message_(std::move(msg)),
    stack_(CurrentThread::stackTrace(/*demangle=*/false))
{}

}