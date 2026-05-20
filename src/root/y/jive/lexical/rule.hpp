
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
                static const unsigned Emit     = 0x01;              //!< emit lexeme
                static const unsigned Drop     = 0x02;              //!< drop lexeme
                static const unsigned ProcMask = Emit|Drop;         //!< emit|drop
                static const unsigned Call     = 0x04;              //!< call scanner
                static const unsigned Back     = 0x08;              //!< back from scanner
                static const unsigned Jump     = 0x10;              //!< jump to scanner
                static const unsigned CntlMask = Call|Back|Jump;    //!< call|back|jump
                static const unsigned UsedMask = ProcMask|CntlMask; //!< usage mask
                static const unsigned Endl     = 0x80;              //!< propagate endl

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param ruleName rule name
                 \param ruleForm rule pattern, EXCEPTION iff FRAIL
                 \param ruleDeed behavior
                 \param ruleInfo parameters for behavior
                 */
                explicit Rule(const Identifier & ruleName,
                              const Motif      & ruleForm,
                              const unsigned     ruleDeed,
                              const Identifier & ruleInfo);

                //! cleanup
                virtual ~Rule() noexcept;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Identifier name; //!< name
                const Motif      form; //!< matching motif
                const unsigned   deed; //!< encoded action
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

