
#include "y/jive/syntax/grammar/core.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            XNode * CoreGrammar:: run(Lexer &lexer, Source &source) const
            {
                assert(rules.size>0);
                Framework     framework(lexer,source);
                const Rule &  rule    = *rules.head;
                const Outcome outcome = rule.accepts(framework);
                return 0;
            }
        }

    }

}

