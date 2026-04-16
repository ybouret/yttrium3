#include "y/apex/rational.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;
using namespace Apex;

Y_UTEST(apex_q)
{
    Core::Rand ran;

    { apq q; std::cerr << q << std::endl; }

    {
        for(size_t iter=0;iter<10;++iter)
        {
            const apz numer(ran, ran.in<size_t>(0,8) );
            const apn denom(ran, ran.in<size_t>(1,8) );
            const apq q(numer,denom);

            std::cerr << numer << "/" << denom << " => " << q << std::endl;
        }
    }



}
Y_UDONE()


