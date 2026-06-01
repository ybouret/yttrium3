
#include "y/jive/syntax/defs.hpp"


namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            const char * HumanReadableKind(const Kind kind) noexcept
            {
                switch(kind)
                {
                    case IsTerminal: return "terminal";
                    case IsInternal: return "internal";
                }
                return Core::Unknown;
            }

        }

    }

}

