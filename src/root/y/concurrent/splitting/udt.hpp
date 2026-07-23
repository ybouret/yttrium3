
//! \file

#ifndef Y_Concurrent_Splitting_UDT_Included
#define Y_Concurrent_Splitting_UDT_Included 1

#include "y/concurrent/subdivision.hpp"
#include "y/container/matrix/coord.hpp"
#include "y/calculus/alignment.hpp"

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

            class UpperDiagonalTile : public Subdivision
            {
            public:
                typedef UpperDiagonalSegment Segment;
                static const size_t Precomputed = 2;
                static const size_t NeededBytes = Precomputed * sizeof(Segment);
                static const size_t NeededWords = Alignment::WordsGEQ<NeededBytes>::Count;

                typedef Segment (UpperDiagonalTile::*Get)(const size_t) const;

                explicit UpperDiagonalTile(const size_t mySize,
                                           const size_t myRank,
                                           Lockable &   myLock,
                                           const size_t extent) noexcept;

                virtual ~UpperDiagonalTile() noexcept;

                virtual bool isEmpty() const noexcept;


                size_t getRow(const size_t k) const noexcept;
                size_t getCol(const size_t k, const size_t r) const noexcept;

                MatrixCoord coord(const size_t k) const noexcept;

                const size_t    n;                 //!< n x n array
                const size_t    span;              //!< segments
                Get const       get;               //!< get method
                Segment * const cxx;               //!< cxx[1..2]
                void *          wksp[NeededWords]; //!< inner space
                const size_t    B;                 //!< 1 + 2*n*
                const size_t    B2;                //!< B^2
                const size_t    kNumber;           //!< n*(n+1)/2
                const size_t    kOffset;           //!< initial valid k
                const size_t    kLength;           //!< number of indices, 0 meanms empty
                const size_t    kUtmost;           //!< utmost  valid k

            private:
                Y_Disable_Copy_And_Assign(UpperDiagonalTile);
                void setup() noexcept;

                Segment Get1(const size_t) const noexcept;
                Segment Get2(const size_t) const noexcept;
                Segment GetN(const size_t) const noexcept;
            };



           


        }

    }

}

#endif // !Y_Concurrent_Splitting_UDT_Included

