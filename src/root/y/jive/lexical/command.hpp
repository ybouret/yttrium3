
//! \file

#ifndef Y_Jive_Lexical_Command_Included
#define Y_Jive_Lexical_Command_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {

            class Command
            {
            public:
                enum Kind
                {
                    Call,
                    Back,
                    Jump,
                    Quit
                };

                Command() noexcept;
                ~Command() noexcept;
                void reset() noexcept;

                const Kind           kind;
                const String * const args;
            private:
                Y_Disable_Copy_And_Assign(Command);
            };
            
        }
    }

}

#endif // !Y_Jive_Lexical_Command_Included

