
//! \file

#ifndef Y_Jive_Lexical_Rule_Included
#define Y_Jive_Lexical_Rule_Included 1

#include "y/jive/pattern.hpp"
#include "y/functor.hpp"
#include "y/pointer/easy.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            typedef Functor<void,TL1(Token)> ActionType;

            class Action : public ActionType, public Counted
            {
            public:
                template <typename OBJECT_POINTER, typename METHOD_POINTER> inline
                explicit Action(OBJECT_POINTER * const objectPointer, METHOD_POINTER * methodPointer) :
                ActionType(objectPointer,methodPointer)
                {
                }
                
                virtual ~Action() noexcept;
            private:
                Y_Disable_Copy_And_Assign(Action);
            };


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
                static const unsigned   Emit     = 0x0001;            //!< emit lexeme
                static const unsigned   Drop     = 0x0002;            //!< drop lexeme
                static const unsigned   ProcMask = Emit|Drop;         //!< emit|drop
                static const unsigned   Call     = 0x0100;            //!< call scanner
                static const unsigned   Back     = 0x0200;            //!< back from scanner
                static const unsigned   Jump     = 0x0400;            //!< jump to scanner
                static const unsigned   CntlMask = Call|Back|Jump;    //!< call|back|jump
                static const unsigned   UsedMask = ProcMask|CntlMask; //!< usage mask
                static const unsigned   Endl     = 0x8000;            //!< propagate endl
                typedef CxxListOf<Rule> List;
                typedef EasyPtr<Action> Hook;

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
                 \param ruleHook
                 */
                explicit Rule(const Identifier & ruleName,
                              const Motif      & ruleForm,
                              const unsigned     ruleDeed,
                              const Identifier & ruleInfo,
                              const Hook       & ruleHook);

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
                Hook             hook; //!< optional action
                Rule *           next; //!< for list
                Rule *           prev; //!< for list

            private:
                Y_Disable_Copy_And_Assign(Rule); //!< discarded
            };
        }


    }
}

#endif // !Y_Jive_Lexical_Rule_Included

