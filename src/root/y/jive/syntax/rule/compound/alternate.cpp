
#include "y/jive/syntax/rule/compound/alternate.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            Alternate:: ~Alternate() noexcept
            {
            }

            const char * Alternate:: vizShape() const noexcept
            {
                return "egg";
            }

            const char * Alternate:: vizStyle() const noexcept
            {
                return "solid";
            }

            

            Y_Jive_Syntax_Rule_Impl(Alternate)
            {
                Y_Jive_Syntax("[|]'" << name << "'");
                const Nesting nest(framework);
                Outcome       last(Rejected,Healthy,Running);
                const Rule   *rule = 0;
                for( const RNode * node = rlist->head;node;node=node->next)
                {
                    const Outcome rout = (**node).accepts(framework);
                    if(Accepted==rout.result)
                    {
                        last = rout;
                        rule = & (**node);
                        if(Healthy == rout.sanity)
                        {
                            break;
                        }
                        // else framework wasn't changed
                    }
                }


                switch(last.result)
                {
                    case Accepted: Y_Jive_Syntax("\\_[+]'" << name << "'=>'" << rule->name << "'"); break;
                    case Rejected: Y_Jive_Syntax("\\_[-]'" << name << "'"); break;
                }

                return last;
            }
        }

    }

}


