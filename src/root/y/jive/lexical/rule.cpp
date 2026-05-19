
#include "y/jive/lexical/rule.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            Rule:: ~Rule() noexcept
            {
                
            }


            Rule:: Rule(const Identifier & ruleName,
                        const Motif      & ruleForm,
                        const unsigned     ruleDeed,
                        const Identifier & ruleInfo) noexcept :
            name(ruleName),
            form(ruleForm),
            deed(ruleDeed),
            info(ruleInfo),
            next(0),
            prev(0)
            {

            }

        }

    }

}

