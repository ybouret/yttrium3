#include "y/apex/natural.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Apex;

Y_UTEST(apex_n)
{
    for(natural_t n=0;n<=10;++n)
    {
        const apn f = apn::factorial(n);
        std::cerr << n << "! = " << f.toDec() << std::endl;
    }
}
Y_UDONE()

