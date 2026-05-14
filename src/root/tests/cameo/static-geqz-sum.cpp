#include "y/cameo/static-geqz-sum.hpp"
#include "y/mkl/xreal.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(cameo_static_geqz_sum)
{

    {
        Cameo::StaticGEQZSum<float,4> sum;
        sum << 3 << 2 << 1 << 4;
        std::cerr << sum() << std::endl;
    }


    {
        Cameo::StaticGEQZSum< XReal<long double>,4> sum;
        sum << 3 << 2 << 1 << 4;
        std::cerr << sum() << std::endl;
    }


}
Y_UDONE()

