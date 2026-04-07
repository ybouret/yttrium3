
#include "y/threading/multi-threaded-object.hpp"
#include "y/concurrent/mutex.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(threading_mto)
{
    Y_SIZEOF(Concurrent::Mutex);
    Y_SIZEOF(MultiThreadedObject);

    {
        const MultiThreadedObject cls;
        {
            MultiThreadedObject::Lock guard(cls);
        }
    }

    {
        MultiThreadedObject cls;
        Y_Lock(cls);
    }



}
Y_UDONE()

