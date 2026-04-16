#include "y/apex/natural.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"


using namespace Yttrium;
using namespace Apex;

Y_UTEST(apex_n)
{
    Core::Rand ran;

    for(natural_t n=0;n<=21;++n)
    {
        const apn f = apn::factorial(n);
        std::cerr << std::setw(2) << n << "! = " << std::setw(20) << f << " #bits=" << f.bits() << std::endl;
    }


    std::cerr << "-- testing add/sub" << std::endl;
    for(size_t k=0;k<1024;++k)
    {
        const apn lhs(ran,ran.in<size_t>(0,1000));
        const apn rhs(ran,ran.in<size_t>(0,1000));
        const apn sum = lhs + rhs;
        Y_ASSERT(sum-lhs==rhs);
        const apn cpy = +lhs;
    }

    std::cerr << "-- testing mul/div" << std::endl;
    for(size_t k=0;k<1024;++k)
    {
        const apn lhs(ran,ran.in<size_t>(1,1000));
        const apn rhs(ran,ran.in<size_t>(1,1000));
        const apn prod = lhs * rhs;
        Y_ASSERT(prod/rhs==lhs);
        const apn m = lhs % rhs;
    }

}
Y_UDONE()

