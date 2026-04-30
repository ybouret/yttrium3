#include "y/calculus/non-zero-bits.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(calculus_nzbits)
{
    uint8_t k = 0;
    for(int i=0;i<16;++i)
    {
        for(int j=0;j<16;++j,++k)
        {
            unsigned n = 0;
            for(unsigned b=0;b<8;++b)
            {
                if( 0 != (k&(1<<b)) ) ++n;
            }
            std::cerr << ' ' << n << ',';
        }
        std::cerr << std::endl;
    }
}
Y_UDONE()
