
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

            OutputStream & Option:: vizSelf(OutputStream &fp) const
            {
                nodeName(fp) << '[';
                Label(fp,*name);
                fp << ",shape=diamond";
                return Endl(fp<< ']');
            }


            Y_Jive_Syntax_Rule_Impl(Option)
            {
                const Nesting  nest(framework);
#if 0
                const unsigned outcome = rule.accepts(framework);
                if( outcome & Outcome::Rejected )
                {
                    return (outcome & Outcome::Modifier) | (Outcome::Accepted|Outcome::Weakened);
                }
                else
                {
                    assert(outcome & Outcome::Accepted);
                    return outcome;
                }
#endif
            }
        }

    }

}
