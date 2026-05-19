//! \file

#ifndef Y_Jive_Lexical_Unit_Included
#define Y_Jive_Lexical_Unit_Included 1

#include "y/jive/token.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            class Scanner
            {
            public:

                virtual ~Scanner() noexcept;
                
            private:
                Y_Disable_Copy_And_Assign(Scanner);
            };
        }

    }

}

#endif // !Y_Jive_Lexical_Unit_Included

