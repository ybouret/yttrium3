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
            //__________________________________________________________________
            //
            //
            //
            //! Produce units with a set of rules
            //
            //
            //__________________________________________________________________
            class Scanner
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                
                virtual ~Scanner() noexcept; //!< cleanup
                
            private:
                Y_Disable_Copy_And_Assign(Scanner); //!< discarded
            };
        }

    }

}

#endif // !Y_Jive_Lexical_Unit_Included

