#include "y/concurrent/subdivision.hpp"
#include "y/container/matrix/coord.hpp"

#include "y/utest/run.hpp"
#include "y/concurrent/fake-lock.hpp"

#include "y/calculus/isqrt.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        namespace Splitting
        {

            class UpperDiagonalTile : public Subdivision
            {
            public:

                explicit UpperDiagonalTile(const size_t mySize,
                                           const size_t myRank,
                                           Lockable &   myLock,
                                           const size_t extent) noexcept;

                virtual ~UpperDiagonalTile() noexcept;

                virtual bool isEmpty() const noexcept;


                size_t getRow(const size_t k) const noexcept;
                size_t getCol(const size_t k, const size_t r) const noexcept;

                MatrixCoord coord(const size_t k) const noexcept;

                const size_t n;        //!< n x n array
                const size_t B;        //!< 1 + 2*n*
                const size_t B2;       //!< B^2
                const size_t kNumber;  //!< n*(n+1)/2
                const size_t kOffset;  //!< initial valid k
                const size_t kLength;  //!< number of indices, 0 meanms empty
                const size_t kUtmost;  //!< utmost  valid k
                const size_t h;        //!< height

            private:
                Y_Disable_Copy_And_Assign(UpperDiagonalTile);
                void setup() noexcept;
            };



            bool UpperDiagonalTile:: isEmpty() const noexcept { return kLength <= 0; }

            UpperDiagonalTile:: UpperDiagonalTile(const size_t mySize,
                                                  const size_t myRank,
                                                  Lockable &   myLock,
                                                  const size_t extent) noexcept :
            Subdivision(mySize,myRank,myLock),
            n(extent),
            B(1+(n<<1)),
            B2(B*B),
            kNumber( (n*(n+1)>>1) ),
            kOffset(1),
            kLength( part(kNumber,Coerce(kOffset)) ),
            kUtmost(kOffset + kLength - 1 ),
            h(0)
            {
                setup();
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
                return ( (i*im1)>>1 )+ k - im1*n;
            }

            MatrixCoord UpperDiagonalTile:: coord(const size_t k) const noexcept
            {
                const size_t r = getRow(k);
                const size_t c = getCol(k,r);
                return MatrixCoord(r,c);
            }

            void UpperDiagonalTile:: setup() noexcept
            {
                if(kLength>0)
                {
                    const MatrixCoord ini = coord(kOffset);
                    const MatrixCoord end = coord(kUtmost);
                    Coerce(h) = end.c - ini.c + 1;
                    std::cerr << "ini: " << ini << std::endl;
                    std::cerr << "end: " << end << std::endl;
                    std::cerr << "h  : " << h   << std::endl;
                }
            }

        }
    }

}

using namespace Yttrium;

Y_UTEST(concurrent_updiag)
{
    Concurrent::FakeLock access;

    for(size_t n=1;n<=4;++n)
    {
        std::cerr << std::endl << "n=" << n << std::endl;
        const size_t kmax = (n*(n+1))>>1;
        Concurrent:: Splitting:: UpperDiagonalTile udt(1,0,access,n);
        for(size_t k=1;k<=kmax;++k)
        {
            //const size_t r = udt.getRow(k);
            //const size_t c = udt.getCol(k,r);
            //std::cerr << "\tk = " << std::setw(2) << k << " : r = " << r << " : c = " << c << std::endl;
            const MatrixCoord p = udt.coord(k);
            std::cerr << "\tk = " << std::setw(2) << k << " : " << p << std::endl;
        }

    }

}
Y_UDONE()

