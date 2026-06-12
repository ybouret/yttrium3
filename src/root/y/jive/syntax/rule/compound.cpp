
#include "y/jive/syntax/rule/compound.hpp"
#include "y/string/format.hpp"
#include "y/stream/output.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            Y_Proxy_Impl(Compound,rlist)
            
            Compound:: ~Compound() noexcept
            {
            }


            OutputStream & Compound:: vizLink(OutputStream &fp) const
            {
                const bool show = rlist->size>1;
                unsigned   indx = 1;
                for(const RNode *node=rlist->head;node;node=node->next,++indx)
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
                if(frozen) throw Specific::Exception(name->c_str(), "frozen! cannot append '%s'", r.name->c_str());
                rlist.pushTail(r);
                return *this;
            }

            
        }

    }

}


