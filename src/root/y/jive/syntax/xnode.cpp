#include "y/jive/syntax/xnode.hpp"
#include "y/libc/block/zero.h"
#include "y/type/destruct.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            const char *     XNode:: humanReadableKind() const noexcept
            {
                return HumanReadableKind(kind);
            }


            XNode:: ~XNode() noexcept
            {
                switch(kind)
                {
                    case IsTerminal: Destruct( static_cast<LxPtr *>(addr)  ); break;
                    case IsInternal: Destruct( static_cast<XList *>(addr) ); break;
                }
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
            addr(0),
            wksp()
            {
                new ( Coerce(addr) = Y_BZero(wksp) ) LxPtr(lexeme);
            }

            Lexeme & XNode:: lexeme() noexcept
            {
                assert(kind==IsTerminal);
                LxPtr &p = *static_cast<LxPtr *>(addr); assert(p.isValid());
                return *p;
            }

            const Lexeme & XNode:: lexeme() const noexcept
            {
                assert(kind==IsTerminal);
                LxPtr &p = *static_cast<LxPtr *>(addr); assert(p.isValid());
                return *p;
            }

            XList & XNode:: list() noexcept
            {
                assert(kind==IsInternal);
                return *static_cast<XList *>(addr);
            }


            const XList & XNode:: list() const noexcept
            {
                assert(kind==IsInternal);
                return *static_cast<const XList *>(addr);
            }


            XNode:: XNode(const Identifier &id) noexcept :
            name(id),
            kind(IsInternal),
            next(0),
            prev(0),
            addr(0),
            wksp()
            {
                new ( Coerce(addr) = Y_BZero(wksp) ) XList();
            }


            void XNode:: returnTo(Lexical::Stack &stack) noexcept
            {
                switch(kind)
                {
                    case IsTerminal: stack.push( static_cast<LxPtr *>(addr)->yield()); break;
                    case IsInternal: static_cast<XList*>(addr)->returnTo(stack);       break;
                }
            }


        }
    }
}

