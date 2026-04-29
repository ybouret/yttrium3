
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

    }

}
