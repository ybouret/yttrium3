
//! \file

#ifndef Y_Jive_Syntax_Defs_Included
#define Y_Jive_Syntax_Defs_Included 1

#include "y/config/setup.hpp"


namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            //! top-level kind of rule/terminal
            enum Kind
            {
                IsTerminal, //!< terminal kind
                IsInternal  //!< internal kind
            };

            //! \return human readable kind
            const char * HumanReadableKind(const Kind) noexcept;

        }
    }

}

#endif // !Y_Jive_Syntax_Defs_Included

