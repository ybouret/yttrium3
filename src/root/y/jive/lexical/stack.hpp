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
            //__________________________________________________________________
            //
            //
            //
            //! Stack interface for Lexer
            //
            //
            //__________________________________________________________________
            class Stack
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Stack() noexcept; //!< setup
                virtual ~Stack() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual void push(Unit * const) noexcept = 0; //!< push a new unit on stack

            private:
                Y_Disable_Copy_And_Assign(Stack); //!< discarded
            };
        }

    }
}

#endif // !Y_Jive_Lexical_Stack_Included
