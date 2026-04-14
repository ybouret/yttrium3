#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(calculus_ldiv)
{

    div_t   d   = div(13,7);
    ldiv_t  ld  = ldiv(13,7);
    lldiv_t lld = lldiv(13,7);

    std::cerr << d.quot   << "," << d.rem << std::endl;
    std::cerr << ld.quot  << "," << ld.rem << std::endl;
    std::cerr << lld.quot << "," << lld.rem << std::endl;


}
Y_UDONE()

