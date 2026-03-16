
//! \file

#ifndef Y_Memory_Book_Included
#define Y_Memory_Book_Included 1


#include "y/memory/pages.hpp"
#include "y/memory/metrics.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium
{
    namespace Memory
    {
        //______________________________________________________________________
        //
        //
        //
        //! Multiple page cache in one position
        //
        //
        //______________________________________________________________________
        class Book : public Collectable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const unsigned MinPageShift = Metrics::MinPageShift;           //!< alias
            static const unsigned MaxPageShift = Metrics::MaxPageShift;           //!< alias
            static const unsigned NumPageSlots = 1 + MaxPageShift - MinPageShift; //!< number of different shifts
            static const size_t   Required     = NumPageSlots * sizeof(Pages);    //!< inner memory

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Book(Page::Mill &mill) noexcept; //!< setup slots \param mill page mill
            virtual ~Book()                 noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            //! call gc on each slot \param amount amount to thrash
            virtual void gc(const uint8_t amount) noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Pages &       operator[](const unsigned shift)       noexcept; //!< access \param shift \return matching Pages
            const Pages & operator[](const unsigned shift) const noexcept; //!< access \param shift \return matching Pages

            //! query total available bytes \return sum of all cached bytes
            uint64_t      availableBytes() const noexcept;


        private:
            Y_Disable_Copy_And_Assign(Book); //!< discarded
            Pages * const pages;             //!< in [MinShift:MaxShift]
            void *        wksp[ Alignment::WordsGEQ<Required>::Count ]; //!< inner memory
        };
    }

}
#endif // !Y_Memory_Book_Included
