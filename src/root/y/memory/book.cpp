
#include "y/memory/book.hpp"
#include "y/libc/block/zero.h"
#include "y/type/destruct.hpp"

namespace Yttrium
{
    namespace Memory
    {


        Book:: Book(Page::Mill &mill,
                    Lockable   &lock) noexcept :
        pages(0),
        wksp()
        {
            Coerce(pages) = static_cast<Pages *>( Y_BZero(wksp) ) - MinPageShift;
            for(unsigned shift=MinPageShift;shift<=MaxPageShift;++shift)
            {
                new (pages+shift) Pages(mill,lock,shift);
            }
        }

        Book:: ~Book() noexcept
        {
            for(unsigned shift=MinPageShift;shift<=MaxPageShift;++shift)
                Destruct(pages+shift);
            Y_BZero(wksp);
        }


        Pages & Book:: operator[](const unsigned shift) noexcept
        {
            assert(pages);
            assert(shift>=MinPageShift);
            assert(shift<=MaxPageShift);
            return pages[shift];
        }

        const Pages & Book:: operator[](const unsigned shift) const noexcept
        {
            assert(pages);
            assert(shift>=MinPageShift);
            assert(shift<=MaxPageShift);
            return pages[shift];
        }


        uint64_t Book:: availableBytes() const noexcept
        {
            assert(pages);
            uint64_t sum = 0;
            for(unsigned shift=MinPageShift;shift<=MaxPageShift;++shift)
            {
                const Pages & p = pages[shift];
                sum += p.count() * p.pageBytes;
            }
            return sum;
        }

        void Book:: gc(const uint8_t amount) noexcept
        {
            for(unsigned shift=MinPageShift;shift<=MaxPageShift;++shift)
            {
                pages[shift].gc(amount);
            }
        }

    }

}
