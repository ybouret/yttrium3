#include "y/cameo/sum/static-queued.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;

Y_UTEST(cameo_sum_static_queued)
{

    { Cameo::Sum::StaticQueued<float,5> cs; }
    { Cameo::Sum::StaticQueued< XReal<long double>,8 > cs; }
}
Y_UDONE()


