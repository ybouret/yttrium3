
#include "y/jive/pattern/basic/one-char.hpp"

namespace Yttrium
{
    namespace Jive
    {


        OneChar:: ~OneChar() noexcept
        {
        }

        OneChar:: OneChar(const uint32_t t) noexcept : Pattern(t)
        {
        }

        OneChar:: OneChar(const OneChar &_) noexcept : Pattern(_) {}

        bool OneChar:: sound() const noexcept { return true; }


        bool OneChar:: takes(Token &token, Source &source) const
        {
            assert(0==token.size);
            Char * const ch = source.get(); if(!ch) return false;
            if( found(**ch) )
            {
                token.pushTail(ch);
                return true;
            }
            else
            {
                source.unget(ch);
                return false;
            }
        }
    }

}

