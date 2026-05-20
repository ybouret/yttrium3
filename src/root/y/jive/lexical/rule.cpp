#include "y/jive/lexical/rule.hpp"
#include "y/exception.hpp"

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
                        const Identifier & ruleInfo) :
            name(ruleName),
            form(ruleForm),
            deed(ruleDeed),
            info(ruleInfo),
            next(0),
            prev(0)
            {
                assert(deed);
                
                if(form->frail())
                    throw Specific::Exception(name->c_str(),"cannot use frail rule!");
            }

        }

    }

}

