
#include "y/jive/syntax/rule/all.hpp"
#include "y/libc/block/zero.h"
#include "y/type/destruct.hpp"
#include "y/stream/output.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            OutputStream & XNode:: viz(OutputStream &fp) const
            {
                nodeName(fp);

                if(rule.isTerminal())
                {
                    assert(Terminal::UUID==rule.uuid);
                    const Token    & token  = lexeme();
                    String           label  = *rule.name;
                    if(token.size>0) label += "='" + token.str() + "'";
                    fp << '[';
                    Label(fp,label);
                    rule.vizPpty(fp);
                    Endl(fp<<']');
                }
                else
                {
                    rule.vizSelf(fp);
                    const XList &xlist = list();
                    const bool   xshow = xlist.size>1;
                    unsigned     count = 0;
                    for(const XNode *node=xlist.head;node;node=node->next,++count)
                    {
                        node->viz(fp);
                        to(node,fp);
                        if(xshow)
                        {
                            fp << '[';
                            Label(fp, Decimal(count).c_str() );
                            fp << ']';
                        }
                        Endl(fp);
                    }
                }

                return fp;
            }

        }

    }

}

