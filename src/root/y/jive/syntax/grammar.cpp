
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
        }

    }

}
