
#include "y/threading/multi-threaded-handle.hpp"
#include "y/concurrent/mutex.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(threading_mth)
{
    Concurrent::Mutex   m;
    MultiThreadedHandle cls(m);
    {
        MultiThreadedHandle::Lock guard(cls);
    };
}
Y_UDONE()

