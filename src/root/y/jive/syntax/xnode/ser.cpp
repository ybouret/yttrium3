
#include "y/jive/syntax/xnode.hpp"
#include "y/jive/syntax/rule.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            size_t XNode :: serialize(OutputStream &fp) const
            {
                size_t res = rule.name->serialize(fp);
                if(rule.isTerminal())
                {
                    const Token &token = lexeme();
                    res += token.str().serialize(fp);
                }
                else
                {
                    const XList &xlist = list();
                    res += fp.vbr(xlist.size);
                    for(const XNode *xnode=xlist.head;xnode;xnode=xnode->next)
                    {
                        res += xnode->serialize(fp);
                    }
                }
                return res;
            }
        }

    }

}


