
#include "y/threading/single-threaded-class.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(threading_stc)
{
    SingleThreadedClass cls;
    {
        SingleThreadedClass::Lock guard(cls);
    };
}
Y_UDONE()

