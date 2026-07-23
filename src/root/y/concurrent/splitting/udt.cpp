
#include "y/concurrent/splitting/udt.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Splitting
        {
            UpperDiagonalSegment:: UpperDiagonalSegment(const MatrixCoord c, const size_t w) noexcept :
            start(c), width(w)
            {
                assert(width>0);
            }

            UpperDiagonalSegment:: ~UpperDiagonalSegment() noexcept
            {
            }

            UpperDiagonalSegment:: UpperDiagonalSegment(const UpperDiagonalSegment &uds) noexcept :
            start(uds.start),
            width(uds.width)
            {

            }

        }

    }

}

#include "y/libc/block/zero.h"

namespace Yttrium
{
    namespace Concurrent
    {
        namespace Splitting
        {
            bool UpperDiagonalTile:: isEmpty() const noexcept { return kLength <= 0; }

            UpperDiagonalTile:: UpperDiagonalTile(const size_t mySize,
                                                  const size_t myRank,
                                                  Lockable &   myLock,
                                                  const size_t extent) noexcept :
            Subdivision(mySize,myRank,myLock),
            n(extent),
            span(0),
            get(0),
            cxx(0),
            wksp(),
            B(1+(n<<1)),
            B2(B*B),
            kNumber( (n*(n+1)>>1) ),
            kOffset(1),
            kLength( part(kNumber,Coerce(kOffset)) ),
            kUtmost(kOffset + kLength - 1 )
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
                const size_t r = getRow(k);   assert(r>=1); assert(r<=n);
                const size_t c = getCol(k,r); assert(c>=r); assert(c<=n);
                return MatrixCoord(r,c);
            }

            void UpperDiagonalTile:: setup() noexcept
            {
                Coerce(cxx) = static_cast<Segment *>( Y_BZero(wksp) )-1;
                if(kLength>0)
                {
                    const MatrixCoord ini = coord(kOffset);
                    const MatrixCoord end = coord(kUtmost);
                    switch( Coerce(span) = end.r - ini.r + 1 )
                    {
                        case 1: {
                            Coerce(get) = & UpperDiagonalTile:: Get1;
                            new (cxx+1) Segment(ini,end.c-ini.c+1); // only segment
                        }  break;

                        case 2:
                            Coerce(get) = & UpperDiagonalTile:: Get2;
                            // first segment: fron ini to end or row
                            new (cxx+1) Segment(ini,n-ini.c+1);

                            // second segment: from diag to end
                            new (cxx+2) Segment( MatrixCoord(end.r,end.r), end.c-end.r+1);
                            break;

                        default:
                            assert(span>=3);
                            Coerce(get) = & UpperDiagonalTile:: GetN;

                            // first segment: fron ini to end or row
                            new (cxx+1) Segment(ini,n-ini.c+1);

                            // last segment: from diag to end
                            new (cxx+2) Segment( MatrixCoord(end.r,end.r), end.c-end.r+1);
                            break;
                    }
                    //std::cerr << "ini: " << ini << std::endl;
                    //std::cerr << "end: " << end << std::endl;
                    //std::cerr << "h  : " << span   << std::endl;
                }
            }

            UpperDiagonalTile::Segment UpperDiagonalTile:: Get1(const size_t) const noexcept
            {
                assert(1==span);
                return cxx[1];
            }

            UpperDiagonalTile::Segment UpperDiagonalTile:: Get2(const size_t indx) const noexcept
            {
                assert(2==span);
                assert(indx>=1);
                assert(indx<=2);
                return cxx[indx];
            }

            UpperDiagonalTile::Segment UpperDiagonalTile:: GetN(const size_t indx) const noexcept
            {
                assert(2<span);
                assert(indx>=1);
                assert(indx<=span);
                if(indx<=1)
                    return cxx[1];
                else
                    if(indx>=span)
                        return cxx[2];
                    else
                    {
                        assert(indx>1);
                        assert(indx<span);
                        const size_t r = cxx[1].start.r + indx - 1;
                        return Segment( MatrixCoord(r,r), (n-r)+1);
                    }
            }


            UpperDiagonalTile::Segment UpperDiagonalTile:: operator[](const size_t i) const noexcept
            {
                assert(i>=1);
                assert(i<=span);
                assert(get);
                return (*this.*get)(i);
            }
        }
    }
}
