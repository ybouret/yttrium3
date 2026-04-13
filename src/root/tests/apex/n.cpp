#include "y/apex/natural.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Apex;

Y_UTEST(apex_n)
{
    for(natural_t n=0;n<=21;++n)
    {
        const apn f = apn::factorial(n);
        std::cerr << std::setw(2) << n << "! = " << std::setw(20) << f.toDec() << " #bits=" << f.bits() << std::endl;
    }
}
Y_UDONE()

