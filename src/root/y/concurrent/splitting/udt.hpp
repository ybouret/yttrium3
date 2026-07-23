
//! \file

#ifndef Y_Concurrent_Splitting_UDT_Included
#define Y_Concurrent_Splitting_UDT_Included 1

#include "y/concurrent/subdivision.hpp"
#include "y/container/matrix/coord.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Splitting
        {
            class UpperDiagonalSegment
            {
            public:
                UpperDiagonalSegment(const MatrixCoord &c, const size_t w) noexcept;
                UpperDiagonalSegment(const UpperDiagonalSegment &) noexcept;
                ~UpperDiagonalSegment() noexcept;

                const MatrixCoord start;
                const size_t      width;

            private:
                Y_Disable_Assign(UpperDiagonalSegment);
            };

           

        }

    }

}

#endif // !Y_Concurrent_Splitting_UDT_Included

