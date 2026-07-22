#include "y/concurrent/splitting/tile1d.hpp"
#include "y/utest/run.hpp"

#include "y/calculus/isqrt.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        namespace Splitting
        {

            class UpperDiagonalTile
            {
            public:



                static size_t GetI(const size_t k) noexcept
                {
                    const size_t D = (k<<3)-3;
                    const size_t S = IntegerSquareRoot(D);
                    return (1+S)>>1;
                }




            private:
                Y_Disable_Copy_And_Assign(UpperDiagonalTile);
            };
        }
    }

}

using namespace Yttrium;

Y_UTEST(concurrent_updiag)
{

    for(size_t n=1;n<=5;++n)
    {
        std::cerr << std::endl;
        const size_t kmax = (n*(n+1))/2;
        std::cerr << "n=" << n << " => kmax=" << kmax << std::endl;
        for(size_t k=1;k<=kmax;++k)
        {
            std::cerr << "k=" << k;
            const size_t i = Concurrent::Splitting::UpperDiagonalTile::GetI(k);
            std::cerr << " | i=" << i;
            const size_t j = i + (k-(1+i*(i-1)/2));
            std::cerr << " | j=" << j;

            std::cerr << std::endl;

        }


    }

}
Y_UDONE()

