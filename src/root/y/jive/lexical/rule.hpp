
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
                static const unsigned Emit = 0x01;
                static const unsigned Drop = 0x02;
                static const unsigned Call = 0x04;
                static const unsigned Back = 0x08;
                static const unsigned Jump = 0x10;
                static const unsigned Endl = 0x80;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Rule(const Identifier & ruleName,
                              const Motif      & ruleForm,
                              const unsigned     ruleDeed,
                              const Identifier & ruleInfo) noexcept;

                virtual ~Rule() noexcept;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Identifier name; //!< name
                const Motif      form; //!< matching motif
                const unsigned   deed;
                const Identifier info; //!< name of argument for call/jump
                Rule *           next; //!< for list
                Rule *           prev; //!< for list
            private:
                Y_Disable_Copy_And_Assign(Rule); //!< discarded
            };
        }

        
    }
}

#endif // !Y_Jive_Lexical_Rule_Included

