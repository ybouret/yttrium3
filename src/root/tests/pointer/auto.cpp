#include "y/pointer/auto.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(pointer_auto)
{

    AutoPtr<int> a;              std::cerr << a << std::endl;
    AutoPtr<int> b = new int(3); std::cerr << b << std::endl;
    a = b;
    std::cerr << a << std::endl;
    std::cerr << b << std::endl;
    a.xch(b);
    std::cerr << a << std::endl;
    std::cerr << b << std::endl;
}
Y_UDONE()
