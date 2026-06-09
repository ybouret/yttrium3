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

        }
    }
}


