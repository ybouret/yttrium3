
#include "y/jive/syntax/xnode.hpp"
#include "y/jive/syntax/rule/all.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            bool XNode:: AreEqual(const XNode &lhs, const XNode &rhs) noexcept
            {
                const Rule &   L    = lhs.rule;
                const Rule &   R    = rhs.rule;
                if(L.uuid  !=  R.uuid) return false;
                if(*L.name != *R.name) return false;

                if(L.isTerminal())
                {
                    assert(R.isTerminal());
                    return lhs.lexeme() == rhs.lexeme();
                }
                else
                {
                    assert(R.isInternal());
                    const XList &ll = lhs.list();
                    const XList &rr = rhs.list();
                    const size_t nn = ll.size; if(nn!=rr.size) return false;

                    for(const XNode *l=ll.head,*r=rr.head;l;l=l->next,r=r->next)
                    {
                        if(!AreEqual(*l,*r)) return false;
                    }

                    return true;

                }
            }

            bool operator==(const XNode &lhs, const XNode &rhs) noexcept
            {
                return XNode::AreEqual(lhs,rhs);
            }

            bool operator!=(const XNode &lhs, const XNode &rhs) noexcept
            {
                return !XNode::AreEqual(lhs,rhs);
            }

        }

    }

}
