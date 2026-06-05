
#include "y/jive/syntax/rule/wildcard/option.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            Option:: ~Option() noexcept
            {
            }

            static const char OptSymbol = '?';

            Option:: Option(const Rule &source) :
            Wildcard(new String(source.name->c_str(),source.name->size(),&OptSymbol,1),UUID,source)
            {
            }

            const char *   Option:: vizShape()     const noexcept { return "diamond"; }
            const char *   Option:: vizStyle()     const noexcept { return "solid";   }

            
            Y_Jive_Syntax_Rule_Impl(Option)
            {
                Y_Jive_Syntax("?OPT  [" << name << "]");
                const Nesting  nesting(framework);
                //--------------------------------------------------------------
                //
                // try to accept rule
                //
                //--------------------------------------------------------------
                Outcome        outcome = rule.accepts(framework);

                //--------------------------------------------------------------
                //
                // modify if rejected to fragile/accepted
                //
                //--------------------------------------------------------------
                if(Rejected==outcome.result)
                {
                    outcome.result = Accepted;
                    outcome.sanity = Fragile;
                }
                return outcome;
            }
        }

    }

}
