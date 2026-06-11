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

            namespace
            {
                static inline
                void appendToExpected(Expected &expected, const Rule &after)
                {
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
                        const RNode * const  rnext = rn->next; if(!rnext) break;                // no next rule
                        const Rule         & child = **rn;     if(child.isInternal()) continue; // this rule is not a terminal
                        const Terminal     & term  = dynamic_cast<const Terminal &>(child);
                        const Rule         & after = **rnext;
                        std::cerr << "   |_'" << term.name << "' => '" << after.name << "'" << std::endl;
                        appendToExpected(Coerce(*term.exdb),after);
                    }
                }
            }


        }
    }
}


