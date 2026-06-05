
#include "y/memory/embed.hpp"
#include "y/calculus/alignment.hpp"
#include <iostream>

namespace Yttrium
{
    namespace Memory
    {

        Embed:: Embed(const Embed &em) noexcept :
        pblock(em.pblock),
        length(em.length),
        offset(em.offset)
        {
        }

        Embed:: ~Embed() noexcept
        {

        }

        size_t Embed:: nextOffset() const noexcept
        {
            return Alignment::SystemMemory::Ceil(offset+length);
        }


        void Embed:: assignFrom(void * const entry) noexcept
        {
            assert(entry);
            assert(pblock);
            *pblock = static_cast<char *>(entry)+offset;
        }

        std::ostream & operator<<(std::ostream &os, const Embed &em)
        {
            return os << "@" << em.offset << "+" << em.length;
        }

        size_t Embed:: Format(Embed        embed[],
                              const size_t count) noexcept
        {
            assert(embed);
            assert(count>0);
            embed[0].offset = 0; assert(0!=embed[0].pblock);
            for(size_t i=1;i<count;++i)
            {
                embed[i].offset = embed[i-1].nextOffset();
            }
            return embed[count-1].nextOffset();
        }

        void  Embed:: Assign(void * const entry,
                             Embed        embed[],
                             const size_t count) noexcept
        {
            assert(embed);
            assert(count>0);
            for(size_t i=0;i<count;++i)
                embed[i].assignFrom(entry);
        }



    }



}


