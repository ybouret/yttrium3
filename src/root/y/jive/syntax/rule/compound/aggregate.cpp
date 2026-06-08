#include "y/jive/syntax/rule/compound/aggregate.hpp"
#include "y/stream/output.hpp"
#include "y/jive/syntax/xnode.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            Aggregate:: ~Aggregate() noexcept
            {
            }

            const char * Aggregate:: vizShape() const noexcept
            {
                return "house";
            }

            const char * Aggregate:: vizStyle() const noexcept
            {
                return "solid";
            }



            Y_Jive_Syntax_Rule_Impl(Aggregate)
            {
                Y_Jive_Syntax("?AGG : [" << name << "]");
                //--------------------------------------------------------------
                //
                //
                // initialize
                //
                //
                //--------------------------------------------------------------
                const Nesting nesting(framework);
                Framework     workspace(Replicate,framework);
                XList &       xlist = workspace.set( XNode::Create(*this) )->list();
                Outcome       outcome(Accepted,Healthy,Running);

                //--------------------------------------------------------------
                //
                //
                // loop on all rules
                //
                //
                //--------------------------------------------------------------
                for(const RNode *node=list.head;node;node=node->next)
                {
                    const Rule    & rule = **node;
                    const Outcome   rout = rule.accepts(workspace);
                    if(rout.status==Blocked) outcome.status = Blocked;
                    if(rout.result==Rejected) {
                        outcome.result = Rejected;
                        break;
                    }
                }

                //--------------------------------------------------------------
                //
                //
                // study result
                //
                //
                //--------------------------------------------------------------
                if(xlist.size<=0)
                    outcome.sanity = Fragile;

                switch(outcome.result)
                {
                    case Rejected:
                        Y_Jive_Syntax("[-][" << name << "]");
                        workspace.dump();
                        break;
                        
                    case Accepted:
                        Y_Jive_Syntax("[+][" << name << "]");
                        switch(duty)
                        {
                            case Entitled: framework.grow( workspace.yield() ); break;
                            case Grouping: framework.join( workspace );         break;
                            case Yielding:
                                if(1==xlist.size)
                                    framework.grow( workspace.yield() );
                                else
                                    framework.join( workspace );
                                break;
                        }
                        break;
                }

                return outcome;
            }
        }

    }

}


