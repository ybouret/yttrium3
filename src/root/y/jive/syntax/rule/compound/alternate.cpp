
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
                const Nesting nesting(framework);
                Outcome       outcome(Rejected,Healthy,Running);

                for( const RNode * node = list.head;node;node=node->next)
                {
                    const Outcome rout = (**node).accepts(framework);
                    if(Accepted==rout.result)
                    {
                        outcome.result = Accepted;
                        outcome.status = rout.status;
                        if( Healthy == (outcome.sanity = rout.sanity) )
                        {
                            break;
                        }
                    }
                }

                

                return outcome;
            }
        }

    }

}


