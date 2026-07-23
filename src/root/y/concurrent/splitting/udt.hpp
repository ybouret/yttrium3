
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
            //__________________________________________________________________
            //
            //
            //
            //! Upper diagonal segment: coordinate and width
            //
            //
            //__________________________________________________________________
            class UpperDiagonalSegment
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                UpperDiagonalSegment(const MatrixCoord c, const size_t w) noexcept; //!< setup \param c coordinante \param w width
                UpperDiagonalSegment(const UpperDiagonalSegment &)        noexcept; //!< duplicate
                ~UpperDiagonalSegment()                                   noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const MatrixCoord start; //!< starting row/col, col>=row
                const size_t      width; //!< number of columns

            private:
                Y_Disable_Assign(UpperDiagonalSegment); //!< discarded
            };

            //__________________________________________________________________
            //
            //
            //
            //! Upper diagonal tile: contiguous segments
            //
            //
            //__________________________________________________________________
            class UpperDiagonalTile : public Subdivision
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef UpperDiagonalSegment Segment;                                               //!< alias
                static const size_t          Precomputed = 2;                                       //!< precomputed segments
                static const size_t          NeededBytes = Precomputed * sizeof(Segment);           //!< alias
                static const size_t          NeededWords = Alignment::WordsGEQ<NeededBytes>::Count; //!< alias
                typedef Segment (UpperDiagonalTile::*Get)(const size_t) const; //!< prototype

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param mySize mySize > 0
                 \param myRank myRank < mySize
                 \param myLock persistent lock
                 \param extent matrix size
                 */
                explicit UpperDiagonalTile(const size_t mySize,
                                           const size_t myRank,
                                           Lockable &   myLock,
                                           const size_t extent) noexcept;

                virtual ~UpperDiagonalTile() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual bool isEmpty() const noexcept;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                size_t      getRow(const size_t k)                 const noexcept; //!< \param k k < kNumber \return row index
                size_t      getCol(const size_t k, const size_t r) const noexcept; //!< \param k k < kNumber \param r row \return col index
                MatrixCoord coord(const size_t k)                  const noexcept; //!< \param k k < kNumber \return matching coordinate
                Segment     operator[](const size_t)               const noexcept; //!< \return segment in [1:span]

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const size_t    n;                 //!< n x n array
                const size_t    span;              //!< segments
                Get const       get;               //!< get method
                Segment * const cxx;               //!< cxx[1..2]
                void *          wksp[NeededWords]; //!< inner space
                const size_t    B;                 //!< 1 + 2*n*
                const size_t    B2;                //!< B^2
                const size_t    kNumber;           //!< n*(n+1)/2
                const size_t    kOffset;           //!< initial valid k
                const size_t    kLength;           //!< number of indices, 0 means empty
                const size_t    kUtmost;           //!< utmost  valid k

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            private:
                Y_Disable_Copy_And_Assign(UpperDiagonalTile);
                void setup() noexcept;
                Segment Get1(const size_t) const noexcept;
                Segment Get2(const size_t) const noexcept;
                Segment GetN(const size_t) const noexcept;
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
            };



           


        }

    }

}

#endif // !Y_Concurrent_Splitting_UDT_Included

