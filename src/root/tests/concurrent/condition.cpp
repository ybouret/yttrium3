#include "y/concurrent/condition.hpp"
#include "y/concurrent/mutex.hpp"
#include "y/concurrent/thread.hpp"

#include "y/utest/run.hpp"

#include "y/concurrent/singulet.hpp"
#include <cassert>

using namespace Yttrium;

namespace
{
    struct Parameters
    {
        Concurrent::Mutex     * mutex;
        Concurrent::Condition * cond;
        size_t                  ready;
    };

    static void ThreadProc(void * const args)
    {
        assert(args);
        Parameters            & params = *static_cast<Parameters *>(args);
        Concurrent::Mutex     & mutex  = *params.mutex;
        Concurrent::Condition & cond   = *params.cond;
        size_t                & ready  = params.ready;

        mutex.lock();
        ++ready;
        (std::cerr << "Ready=" << ready << std::endl).flush();
        if(ready<3)
            cond.wait(mutex);
        else
            cond.broadcast();
        (std::cerr << "awaken" << std::endl).flush();
        mutex.unlock();

    }

}

Y_UTEST(concurrent_condition)
{
    Concurrent::Singulet::Verbose = true;
    Concurrent::Mutex     mutex;
    Concurrent::Condition cond;

    Parameters params = { &mutex, &cond, 0 };

    Concurrent::Thread t1(ThreadProc,&params);
    Concurrent::Thread t2(ThreadProc,&params);
    Concurrent::Thread t3(ThreadProc,&params);

    if(false)
    {
        mutex.lock();
        if(params.ready<3)
        {
            cond.wait(mutex);
            Y_CHECK(3==params.ready);
        }
        Y_CHECK(3==params.ready);
        mutex.unlock();
    }

   // cond.signal();
   // cond.signal();
   // cond.signal();







}
Y_UDONE()
