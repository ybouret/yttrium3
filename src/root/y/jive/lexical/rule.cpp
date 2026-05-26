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
                        const Identifier & ruleInfo,
                        Action * const     ruleHook) :
            name(ruleName),
            form(ruleForm),
            deed(ruleDeed),
            info(ruleInfo),
            hook(ruleHook),
            next(0),
            prev(0)
            {
                assert(deed&UsedMask);
                
                if(form->frail())
                    throw Specific::Exception(name->c_str(),"cannot use frail rule!");
            }

        }

    }

}

