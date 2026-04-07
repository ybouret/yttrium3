#include "y/threading/global-multi-threaded.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(threading_gmt)
{
    GlobalMultiThreaded cls;
    {
        GlobalMultiThreaded::Lock guard(cls);

    };
}
Y_UDONE()

