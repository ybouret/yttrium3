#include "y/random/park-miller.hpp"
#include "y/random/mt19937.hpp"
#include "y/random/isaac.hpp"

#include "y/mkl/statistics/variance.hpp"
#include "y/mkl/statistics/average.hpp"
#include "y/utest/run.hpp"

#include "y/container/sequence/vector.hpp"

using namespace Yttrium;


namespace
{

    template <typename T> static inline
    void checkStatsFor(Random::Bits &ran, const size_t n)
    {
        Vector<T>               r(WithAtLeast,n);
        for(size_t i=n;i>0;--i) r << ran.to<T>();
        Cameo::Addition<T>      xadd(n);
        std::cerr << "--     for " << typeid(T).name()  << std::endl;
        const double ave = MKL::Statistics::Average::Of(r,xadd);
        const double var = MKL::Statistics::Variance::Of(r,ave,xadd);
        std::cerr << "--         ave=" << ave << std::endl;
        std::cerr << "--         var=" << var << std::endl;
    }

    template <typename T> static inline
    void checkStatsForIntegral(Random::Bits &ran, const size_t n)
    {
        Vector<long double> r(WithAtLeast,n);
        for(size_t i=n;i>0;--i) r << (long double)ran.to<T>();
        Cameo::Addition<long double>  xadd(n);
        std::cerr << "--     for " << typeid(T).name()  << std::endl;
        const double ave = MKL::Statistics::Average::Of(r,xadd);
        const double var = MKL::Statistics::Variance::Of(r,ave,xadd);
        std::cerr << "--         ave=" << ave << std::endl;
        std::cerr << "--         var=" << var << std::endl;
    }

    static inline void checkStats(Random::Bits &ran)
    {
        std::cerr << "-- " << ran.callSign() << std::endl;


        static const size_t n = 10000;
        checkStatsFor<float>(ran,n);
        checkStatsFor<double>(ran,n);
        checkStatsFor<long double>(ran,n);
        checkStatsFor< XReal<float> >(ran,n);
        checkStatsFor< XReal<double> >(ran,n);
        checkStatsFor< XReal<long double> >(ran,n);

        checkStatsForIntegral<short>(ran,n);
        checkStatsForIntegral<unsigned short>(ran,n);
        


        return;

        Vector<double>      r(WithAtLeast,n);
        for(size_t i=n;i>0;--i) r << ran();

        Cameo::Addition<double> xadd(n);
        const double ave = MKL::Statistics::Average::Of(r,xadd);
        const double var = MKL::Statistics::Variance::Of(r,ave,xadd);
        std::cerr << "\tave=" << ave << std::endl;
        std::cerr << "\tvar=" << var << std::endl;
        std::cerr << std::endl;
    }
}

Y_UTEST(random_uniform32)
{

    Random::ParkMiller ranParkMiller;
    Random::MT19937    ranMT19937;
    Random::ISAAC<4>   ranISAAC4;
    Random::ISAAC<8>   ranISAAC8;

    checkStats(ranParkMiller);
    checkStats(ranMT19937);
    checkStats(ranISAAC4);
    checkStats(ranISAAC8);

}
Y_UDONE()
