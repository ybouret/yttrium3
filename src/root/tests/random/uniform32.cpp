#include "y/random/park-miller.hpp"
#include "y/mkl/statistics/variance.hpp"
#include "y/mkl/statistics/average.hpp"
#include "y/utest/run.hpp"

#include "y/container/sequence/vector.hpp"

using namespace Yttrium;


namespace
{
    static inline void checkStats(Random::Uniform32 &ran)
    {
        static const size_t n = 100000;
        Vector<double>      r(WithAtLeast,n);
        for(size_t i=n;i>0;--i) r << ran();

        Cameo::Addition<double> xadd(n);
        const double ave = MKL::Statistics::Average::Of(r,xadd);
        const double var = MKL::Statistics::Variance::Of(r,ave,xadd);
        std::cerr << "ave=" << ave << std::endl;
        std::cerr << "var=" << var << std::endl;

    }
}

Y_UTEST(random_uniform32)
{

    Random::ParkMiller ran;
    checkStats(ran);

}
Y_UDONE()
