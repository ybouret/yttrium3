
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
            //__________________________________________________________________
            //
            //
            //
            //! Command when control lexeme is met
            //
            //
            //__________________________________________________________________
            class Command
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________

                //! what to do
                enum Kind
                {
                    Call, //!< call another scanner
                    Back, //!< back from current scanner
                    Jump, //!< jump to anotehr scanner
                    Quit  //!< met end of stream
                };

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                Command()    noexcept; //!< setup to quit,null
                ~Command()   noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                void reset() noexcept; //!< reset to quit,null

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Kind           kind; //!< kind
                const String * const args; //!< persistent argument

            private:
                Y_Disable_Copy_And_Assign(Command); //!< cleanup
            };
            
        }
    }

}

#endif // !Y_Jive_Lexical_Command_Included

