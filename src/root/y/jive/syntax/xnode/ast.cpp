

#include "y/jive/syntax/xnode.hpp"
#include "y/jive/syntax/rule/terminal.hpp"
#include "y/jive/syntax/rule/compound/aggregate.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            static inline XNode * TerminalAST(XNode * const xnode) noexcept
            {
                assert(xnode);
                assert(xnode->rule.isTerminal());
                assert(Terminal::UUID == xnode->rule.uuid);
                const Terminal &t = dynamic_cast<const Terminal &>(xnode->rule);

                switch(t.load)
                {
                    case Standard: break;
                    case Univocal: xnode->lexeme().release(); break;
                }

                return xnode;
            }

            static inline void InternalAST(XNode *const xnode) noexcept
            {
                assert(xnode);
                assert(xnode->rule.isInternal());

                XList &source = xnode->list();
                {
                    XList  target;
                    while(source.size)
                    {
                        AutoPtr<XNode> child = XNode::AST(source.popHead());

                        switch(child->rule.uuid)
                        {
                            case Terminal::UUID:
                                switch(dynamic_cast<const Terminal &>(child->rule).role)
                                {
                                    case Semantic: break;
                                    case Dividing: continue;
                                }
                                break;

                            case Aggregate::UUID:
                                switch(dynamic_cast<const Aggregate &>(child->rule).duty)
                                {
                                    case Entitled: break;
                                    case Grouping: target.mergeTail(child->list()); continue;
                                    case Yielding:
                                        if(1==child->list().size) { target.mergeTail(child->list()); continue; }
                                        break;
                                }
                                break;

                            default:
                                break;
                        }
                        target.pushTail(child.yield());
                    }

                    target.swapForList(source);
                }

            }


            XNode * XNode:: AST( XNode * const xnode ) noexcept
            {
                assert(xnode);

                switch(xnode->rule.kind)
                {
                    case IsTerminal: return TerminalAST(xnode);
                    case IsInternal:        InternalAST(xnode); break;
                }
                return xnode;
            }

        }
    }

}


