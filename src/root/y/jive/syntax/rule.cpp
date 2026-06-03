
#include "y/jive/syntax/rule.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            bool Rule::Verbose = false;
            
            const char * Rule:: humanReadableKind() const noexcept
            {
                return HumanReadableKind(kind);
            }

            Rule:: ~Rule() noexcept
            {
            }

            OutputStream & Rule:: vizLink(OutputStream &fp) const
            {
                return fp;
            }

            bool Rule:: isInternal() const noexcept { return IsInternal == kind; }
            bool Rule:: isTerminal() const noexcept { return IsTerminal == kind; }

        }

    }

}


