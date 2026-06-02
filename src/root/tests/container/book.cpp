#include "y/container/associative/book.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;

#include "y/object.hpp"
#include "y/pointer/auto.hpp"

Y_UTEST(container_book)
{
    {
        int a = 7;
        AddrKey k(a);
        std::cerr << (void*) &a << " => " << k << std::endl;
    }

    {
        AutoPtr<Object> p = new Object();
        Object &r = *p;
        AddrKey k(r);
        std::cerr << (void*) &r << " => " << k << std::endl;
    }
}
Y_UDONE()

