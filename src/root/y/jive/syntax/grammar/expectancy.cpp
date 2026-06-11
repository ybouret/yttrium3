#include "y/jive/syntax/rule/all.hpp"
#include "y/jive/syntax/grammar/core.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {
            void CoreGrammar:: noExpectancy() noexcept
            {
                for(Rule *rule=rules.head;rule;rule=rule->next)
                {
                    if(rule->isInternal()) continue;
                    dynamic_cast<Terminal *>(rule)->exdb->free();
                }
            }

            void CoreGrammar:: buildExpectancy()
            {
                noExpectancy();


                //--------------------------------------------------------------
                //
                //
                // loop on top-level aggregates
                //
                //
                //--------------------------------------------------------------
                for(Rule *rule=rules.head;rule;rule=rule->next)
                {
                    if(rule->uuid!=Aggregate::UUID) continue;
                    std::cerr << "-- need to study " << rule->name << std::endl;

                    //----------------------------------------------------------
                    //
                    //
                    // loop on top-level aggregates
                    //
                    //
                    //----------------------------------------------------------
                    const Aggregate &parent = *dynamic_cast<const Aggregate *>(rule);
                    for(const RNode *rn=parent->head;rn;rn=rn->next)
                    {
                        const RNode * const  rnxt = rn->next; if(!rnxt) break;                // no next rule
                        const Rule         & chld = **rn;     if(chld.isInternal()) continue; // this rule is not a terminal
                        const Terminal     & term = dynamic_cast<const Terminal &>(chld);
                        const Rule         & next = **rnxt;
                        std::cerr << "   |_'" << term.name << "' => '" << next.name << "'" << std::endl;
                    }
                }
            }


        }
    }
}


