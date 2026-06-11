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
                void queryFirstInAggregate(Expected         &expected,
                                           const Aggregate  &agg,
                                           BookOfRules      &visited)
                {
                    assert(visited.query(agg));
                    for(const RNode *rn=agg->head;rn;rn=agg->head)
                    {
                    }


                }

                static inline
                void queryFirstExpected(Expected    &expected,
                                        const Rule  &after,
                                        BookOfRules &visited)
                {
                    if( !visited.write(after) ) return; // already visited
                   // std::cerr << "\t\tgot " << after << std::endl;
                    switch(after.uuid)
                    {
                        case Terminal::UUID:(void)expected.write(after); return;
                        case Alternate::UUID:
                            for(const RNode *rn=dynamic_cast<const Alternate&>(after)->head;rn;rn=rn->next)
                            {
                                queryFirstExpected(expected,**rn,visited);
                            }
                            break;

                        case Repeat::UUID:
                        case Option::UUID:
                            queryFirstExpected(expected, dynamic_cast<const Wildcard &>(after).rule, visited);
                            break;

                        case Aggregate::UUID:
                            queryFirstInAggregate(expected,
                                                  dynamic_cast<const Aggregate &>(after),
                                                  visited);
                            break;

                        default:
                            std::cerr << "no done yet uuid='%s'" << FourCC(after.uuid) << std::endl;
                            break;
                    }

                }
            }

            void CoreGrammar:: buildExpectancy()
            {
                noExpectancy();

                BookOfRules visited;

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
                    //std::cerr << "-- need to study " << rule->name << std::endl;

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
                        visited.free();
                        queryFirstExpected(Coerce(*term.exdb),after,visited);
                        std::cerr << "    |_" << *term.exdb << std::endl;
                    }
                }
            }


        }
    }
}


