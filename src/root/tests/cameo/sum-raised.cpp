
#include "y/cameo/sum/raised.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(cameo_sum_raised)
{
    { Cameo::Sum::Raised<int>      cs; }
    { Cameo::Sum::Raised<uint16_t> cs; }

}
Y_UDONE()


