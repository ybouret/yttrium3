
#include "y/jive/syntax/rule/compound.hpp"
#include "y/string/format.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            Compound:: ~Compound() noexcept
            {
            }


            OutputStream & Compound:: vizLink(OutputStream &fp) const
            {
                const bool show = list.size>1;
                unsigned   indx = 1;
                for(const RNode *node=list.head;node;node=node->next,++indx)
                {
                    to(& **node,fp);
                    if(show)
                    {
                        const String label = Formatted::Get("%u",indx);
                        Label( fp << '[', label ) << ']';
                    }
                    Endl(fp);
                }
                return fp;
            }

            Compound & Compound:: operator<<(const Rule &r)
            {
                pushTail(r);
                return *this;
            }

            
        }

    }

}


