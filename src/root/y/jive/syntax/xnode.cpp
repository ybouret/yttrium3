#include "y/jive/syntax/xnode.hpp"
#include "y/libc/block/zero.h"
#include "y/type/destruct.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {


            XNode:: ~XNode() noexcept
            {
                switch(rule.kind)
                {
                    case IsTerminal: Destruct( static_cast<LxPtr *>(addr)  ); break;
                    case IsInternal: Destruct( static_cast<XList *>(addr) ); break;
                }
            }

            

            XNode:: XNode(const Rule &   xrule,
                          Lexeme * const lexeme) noexcept :
            rule(xrule),
            next(0),
            prev(0),
            addr(0),
            wksp()
            {
                assert(IsTerminal==rule.kind);
                assert(0!=lexeme);
                assert(*lexeme->name==*rule.name);
                new ( Coerce(addr) = Y_BZero(wksp) ) LxPtr(lexeme);
            }

            Lexeme & XNode:: lexeme() noexcept
            {
                assert(rule.kind==IsTerminal);
                LxPtr &p = *static_cast<LxPtr *>(addr); assert(p.isValid());
                return *p;
            }

            const Lexeme & XNode:: lexeme() const noexcept
            {
                assert(rule.kind==IsTerminal);
                LxPtr &p = *static_cast<LxPtr *>(addr); assert(p.isValid());
                return *p;
            }

            XList & XNode:: list() noexcept
            {
                assert(rule.kind==IsInternal);
                return *static_cast<XList *>(addr);
            }


            const XList & XNode:: list() const noexcept
            {
                assert(rule.kind==IsInternal);
                return *static_cast<const XList *>(addr);
            }


            XNode:: XNode(const Rule &xrule) noexcept :
            rule(xrule),
            next(0),
            prev(0),
            addr(0),
            wksp()
            {
                assert(IsInternal==rule.kind);
                new ( Coerce(addr) = Y_BZero(wksp) ) XList();
            }


            void XNode:: returnTo(Lexical::Stack &stack) noexcept
            {
                switch(rule.kind)
                {
                    case IsTerminal: stack.push( static_cast<LxPtr *>(addr)->yield()); break;
                    case IsInternal: static_cast<XList*>(addr)->returnTo(stack);       break;
                }
            }


            void XNode:: Grow(XNode * &tree, XNode * const node) noexcept
            {
                if(0==tree)
                {
                    tree = node;
                }
                else
                {
                    assert(tree->rule.kind == IsInternal);
                    tree->list().pushTail(node);
                }
            }

            XNode * XNode:: Create(const Rule &r, Lexeme * const l)
            {
                assert(l);
                try {
                    return new XNode(r,l);
                }
                catch(...)
                {
                    delete l; throw;
                }
            }


            XNode * XNode:: Create(const Rule &r)
            {
                return new XNode(r);
            }


        }
    }
}

