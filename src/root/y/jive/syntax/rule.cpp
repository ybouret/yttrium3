
#include "y/jive/syntax/rule.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
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



        }

    }

}


