#include "y/threading/global-multi-threaded.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(threading_gmt)
{
    {
        const GlobalMultiThreaded cls;
        {
            GlobalMultiThreaded::Lock guard(cls);
        };
    }

    {
        GlobalMultiThreaded cls;
        Y_Lock(cls);
    }
}
Y_UDONE()

