
#include "y/memory/book.hpp"
#include "y/libc/block/zero.h"
#include "y/type/destruct.hpp"
#include "y/ability/lockable.hpp"
#include "y/stream/xmlog.hpp"

namespace Yttrium
{
    namespace Memory
    {


        Book:: Book(PageFactory &mill,
                    Lockable    &lock) noexcept :
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
            Pages * const first = pages+MinPageShift;
            Y_Lock(first->access);
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
            Pages * const first = pages+MinPageShift;
            Y_Lock(first->access);
            for(unsigned shift=MinPageShift;shift<=MaxPageShift;++shift)
            {
                pages[shift].gc(amount);
            }
        }

        const unsigned Book::NumPageSlots;

        void Book:: toXML(XML::Log &xml) const
        {
            Pages * const first = pages+MinPageShift;
            Y_Lock(first->access);
            Y_XML_Element_Attr(xml,book,Y_XML_Attr(NumPageSlots));
            for(unsigned shift=MinPageShift;shift<=MaxPageShift;++shift)
            {
                const Pages &p = pages[shift];
                if(p->size) p.toXML(xml);
            }
        }
    }

}
