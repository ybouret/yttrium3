#include "y/calculus/base2.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(calculus_base2)
{

    for(size_t i=0;i<=100;++i)
    {
        std::cerr << i << " => " << NextPowerOfTwo(i) << std::endl;
    }

}
Y_UDONE()

