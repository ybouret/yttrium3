#include "y/jive/syntax/xnode.hpp"
#include "y/libc/block/zero.h"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            XNode:: ~XNode() noexcept
            {
            }


            XNode:: XNode(Lexeme * const lexeme) noexcept :
            name(lexeme->name),
            kind(IsTerminal),
            next(0),
            prev(0),
            wksp()
            {
                new ( Y_BZero(wksp) ) LPtr(lexeme);
            }


        }
    }
}

