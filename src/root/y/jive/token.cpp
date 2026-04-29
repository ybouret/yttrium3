
#include "y/jive/token.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Token:: ~Token() noexcept
        {
        }

        Token:: Token(const Token &t) : CxxList(t) {}

        Token:: Token() noexcept
        {
        }

        Token & Token:: operator<<(Char * const ch) noexcept
        {
            pushTail(ch);
            return *this;
        }


        Token & Token:: operator>>(Char * const ch) noexcept
        {
            pushHead(ch);
            return *this;
        }


    }

}
