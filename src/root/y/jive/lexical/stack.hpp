//! \file

#ifndef Y_Jive_Lexical_Stack_Included
#define Y_Jive_Lexical_Stack_Included 1

#include "y/jive/lexical/unit.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {

            class Stack
            {
            public:
                explicit Stack() noexcept;
                virtual ~Stack() noexcept;

                virtual void         push(Unit * const) noexcept = 0;

            private:
                Y_Disable_Copy_And_Assign(Stack);
            };
        }

    }
}

#endif // !Y_Jive_Lexical_Stack_Included
