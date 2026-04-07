
#include "y/threading/single-threaded-class.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(threading_stc)
{
    {
        const SingleThreadedClass cls;
        {
            SingleThreadedClass::Lock guard(cls);
        };
    }

    {
        SingleThreadedClass cls;
        Y_Lock(cls);
    }
}
Y_UDONE()

