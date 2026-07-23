
#include "y/concurrent/splitting/udt.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Splitting
        {
            UpperDiagonalSegment:: UpperDiagonalSegment(const MatrixCoord &c, const size_t w) noexcept :
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


namespace Yttrium
{
    namespace Concurrent
    {
        namespace Splitting
        {
            
        }
    }
}
