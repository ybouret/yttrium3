
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
                Y_Jive_Syntax("?ALT  [" << name << "]");
                const Nesting nest(framework);
                Outcome       last(Rejected,Healthy,Running);
                for( const RNode * node = list.head;node;node=node->next)
                {
                    const Outcome rout = (**node).accepts(framework);
                    if(Accepted==rout.result)
                    {
                        last = rout;
                        if(Healthy == rout.sanity)
                        {
                            break;
                        }
                        // else framework wasn't changed
                    }
                }


                return last;
            }
        }

    }

}


