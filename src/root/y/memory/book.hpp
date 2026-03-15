
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

        class Book : public Collectable
        {
        public:
            static const unsigned MinPageShift = Metrics::MinPageShift;
            static const unsigned MaxPageShift = Metrics::MaxPageShift;
            static const unsigned NumPageSlots = 1 + MaxPageShift - MinPageShift;
            static const size_t   Required     = NumPageSlots * sizeof(Pages);

            explicit Book(Page::Mill &mill) noexcept;
            virtual ~Book()                 noexcept;

            virtual void gc(const uint8_t amount) noexcept;
            
            Pages &       operator[](const unsigned shift) noexcept;
            const Pages & operator[](const unsigned shift) const noexcept;

            uint64_t      availableBytes() const noexcept;


        private:
            Y_Disable_Copy_And_Assign(Book);
            Pages * const pages;
            void *        wksp[ Alignment::WordsGEQ<Required>::Count ];
        };
    }

}
#endif // !Y_Memory_Book_Included
