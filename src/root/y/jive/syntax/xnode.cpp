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

            namespace
            {
                static inline Lexeme * CheckLexeme(Lexeme * const lexeme) noexcept
                {
                    assert(lexeme);
                    return lexeme;
                }
            }

            XNode:: XNode(Lexeme * const lexeme) noexcept :
            name(CheckLexeme(lexeme)->name),
            kind(IsTerminal),
            next(0),
            prev(0),
            wksp()
            {
                new ( Y_BZero(wksp) ) LPtr(lexeme);
            }


            XNode:: XNode(const Identifier &id) noexcept :
            name(id),
            kind(IsInternal),
            next(0),
            prev(0),
            wksp()
            {
                new ( Y_BZero(wksp) ) XList();
            }


        }
    }
}

