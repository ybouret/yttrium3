
#include "y/cameo/sum/queued.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;

Y_UTEST(cameo_sum_queued)
{

    { Cameo::Sum::Queued<float> cs; }
    { Cameo::Sum::Queued< XReal<long double> > cs; }

}
Y_UDONE()


