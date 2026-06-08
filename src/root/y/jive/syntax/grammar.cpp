
#include "y/jive/syntax/grammar.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            Grammar:: ~Grammar() noexcept
            {
            }


            const Rule & Grammar:: rep(const Rule &rule, const size_t nmin)
            {
                assert( rules.owns(&rule) );
                return add( new Repeat(rule,nmin) );
            }

            const Rule & Grammar:: opt(const Rule &rule)
            {
                assert( rules.owns(&rule) );
                return add( new Option(rule) );
            }

            const Rule & Grammar:: oom(const Rule &rule)
            {
                return rep(rule,1);
            }

            const Rule & Grammar:: zom(const Rule &rule)
            {
                return rep(rule,0);
            }

            const Rule &  Grammar:: pick(const Rule &a, const Rule &b)
            {
                const Rule *       arr[2] = { &a, &b };
                const Identifier   uid( MakeName(arr,2,'|') );
                return alt(uid) << a << b;
            }

            const Rule &  Grammar:: pick(const Rule &a, const Rule &b, const Rule &c)
            {
                const Rule *       arr[3] = { &a, &b, &c };
                const Identifier   uid( MakeName(arr,3,'|') );
                return alt(uid) << a << b << c;
            }


            const Rule &  Grammar:: cat(const Rule &a, const Rule &b)
            {
                const Rule *       arr[2] = { &a, &b };
                const Identifier   uid( MakeName(arr,2,'&') );
                return grp(uid) << a << b;
            }

            const Rule &  Grammar:: cat(const Rule &a, const Rule &b, const Rule &c)
            {
                const Rule *       arr[3] = { &a, &b, &c };
                const Identifier   uid( MakeName(arr,3,'&') );
                return grp(uid) << a << b << c;
            }


            const Rule * Grammar:: queryRule(const String &ruleName) const noexcept
            {
                for(const Rule *rule=rules.head;rule;rule=rule->next)
                {
                    if(ruleName==*rule->name)
                        return rule;
                }
                return 0;
            }

        }

    }

}
