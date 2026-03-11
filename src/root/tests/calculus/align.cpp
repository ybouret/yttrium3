
#include "y/calculus/alignment.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(calculus_align)
{

    for(size_t i=0;i<=10;++i)
    {
        std::cerr << Alignment::To<void *>::Ceil(i) << std::endl;
    }

}
Y_UDONE()

