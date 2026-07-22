#include "y/concurrent/splitting/tile1d.hpp"
#include "y/utest/run.hpp"

#include "y/calculus/isqrt.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        namespace Splitting
        {

            class UpperDiagonalTile
            {
            public:

                explicit UpperDiagonalTile(const size_t extent) noexcept;

                virtual ~UpperDiagonalTile() noexcept;

                size_t getRow(const size_t k) const noexcept;
                size_t getCol(const size_t k, const size_t i) const noexcept;

                const size_t n;        //!< n x n array
                const size_t B;        //!< 1 + 2*n*
                const size_t B2;       //!< B^2
                const size_t kNumber;  //!< n*(n+1)/2
                const size_t kOffset;  //!< initial valid k
                const size_t kLength;  //!< number of indices, 0 meanms empty
                const size_t kUtmost;  //!< utmost  valid k
                //const size_t h;        //!< height

            private:
                Y_Disable_Copy_And_Assign(UpperDiagonalTile);
            };


            UpperDiagonalTile:: UpperDiagonalTile(const size_t extent) noexcept :
            n(extent),
            B(1+(n<<1)),
            B2(B*B),
            kNumber( (n*(n+1)>>1) ),
            kOffset(1),
            kLength(kNumber),
            kUtmost(kOffset + kLength - 1 )
            {
            }

            UpperDiagonalTile:: ~UpperDiagonalTile() noexcept
            {
            }

            size_t UpperDiagonalTile:: getRow(const size_t k) const noexcept
            {
                assert(k>=1);
                assert(k<=kNumber);
                const size_t Delta = B2 - (k<<3);
                const size_t twice = (B - IntegerSquareRoot(Delta));
                const size_t align = Alignment::On<2>::Ceil(twice);
                return align>>1;
            }

            size_t UpperDiagonalTile:: getCol(const size_t k, const size_t i) const noexcept
            {
                assert(k>=1);
                assert(k<=kNumber);
                const size_t im1 = i-1;
                const size_t kmx = im1*(n+1) - ( (i*im1)>>1 );
                return im1 + k-kmx;
            }


        }
    }

}

using namespace Yttrium;

Y_UTEST(concurrent_updiag)
{

    for(size_t n=1;n<=4;++n)
    {
        std::cerr << std::endl << "n=" << n << std::endl;
        const size_t kmax = (n*(n+1))>>1;
        Concurrent:: Splitting:: UpperDiagonalTile udt(n);
        for(size_t k=1;k<=kmax;++k)
        {
            const size_t r = udt.getRow(k);
            const size_t c = udt.getCol(k,r);
            std::cerr << "\tk=" << std::setw(2) << k << " : r=" << r << " : c=" << c << std::endl;
        }

    }

}
Y_UDONE()

