
//! \file

#ifndef Y_Jive_Lexical_Actions_Included
#define Y_Jive_Lexical_Actions_Included 1

#include "y/jive/lexical/action.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {

            class Actions : public Action::List
            {
            public:
                explicit Actions() noexcept;
                virtual ~Actions() noexcept;

            private:
                Y_Disable_Copy_And_Assign(Actions);
            };

        }

    }

}

#endif // !Y_Jive_Lexical_Actions_Included

