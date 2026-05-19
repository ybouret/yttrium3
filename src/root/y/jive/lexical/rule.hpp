
//! \file

#ifndef Y_Jive_Lexical_Rule_Included
#define Y_Jive_Lexical_Rule_Included 1

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
            //! Rule to govern scanner/lexer when motif is matched
            //
            //
            //__________________________________________________________________
            class Rule : public Object
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________


                virtual ~Rule() noexcept;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Identifier name;   //!< name
                const Motif      motif;  //!< matching motif
                Rule *           next;   //!< for list
                Rule *           prev;   //!< for list
            private:
                Y_Disable_Copy_And_Assign(Rule); //!< discarded
            };
        }

        
    }
}

#endif // !Y_Jive_Lexical_Rule_Included

