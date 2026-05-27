
//! \file

#ifndef Y_Jive_Lexical_Rule_Included
#define Y_Jive_Lexical_Rule_Included 1

#include "y/jive/regexp.hpp"
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
                explicit Action(OBJECT_POINTER * const objectPointer, METHOD_POINTER const methodPointer) :
                ActionType(objectPointer,methodPointer)
                {
                }
                
                virtual ~Action() noexcept;
            private:
                Y_Disable_Copy_And_Assign(Action);
            };

            typedef EasyPtr<Action> RuleHook;


            enum LexemeProcess
            {
                EmitLexeme,
                DropLexeme
            };

            enum EndOfLineFlag
            {
                IsEndOfLine,
                NoEndOfLine
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
                static const unsigned   Hook     = 0x0004;            //!< perform action
                static const unsigned   ProcMask = Emit|Drop|Hook;    //!< emit|drop
                static const unsigned   Call     = 0x0100;            //!< call scanner
                static const unsigned   Back     = 0x0200;            //!< back from scanner
                static const unsigned   Jump     = 0x0400;            //!< jump to scanner
                static const unsigned   CntlMask = Call|Back|Jump;    //!< call|back|jump
                static const unsigned   UsedMask = ProcMask|CntlMask; //!< usage mask
                static const unsigned   Endl     = 0x8000;            //!< propagate endl
                typedef CxxListOf<Rule> List;
                static const char   BackPrefix[]; //! "<-"
                static const size_t BackLength;   //!< strlen(BackPrefix)

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
                 \param ruleInfo parameters for behavior, may default to ruleName
                 \param ruleHook
                 */
                explicit Rule(const Identifier & ruleName,
                              const Motif      & ruleForm,
                              const unsigned     ruleDeed,
                              const Identifier & ruleInfo,
                              const RuleHook   & ruleHook);

                //! cleanup
                virtual ~Rule() noexcept;

                static unsigned DeedFor(const LexemeProcess lxp,
                                        const EndOfLineFlag eol) noexcept
                {
                    unsigned ruleDeed = 0;
                    switch(lxp)
                    {
                        case EmitLexeme: ruleDeed |= Emit; break;
                        case DropLexeme: ruleDeed |= Drop; break;
                    }
                    switch(eol)
                    {
                        case IsEndOfLine: ruleDeed |= Endl; break;
                        case NoEndOfLine:                   break;
                    }
                    return ruleDeed;
                }


                //! creating a rule without hook
                /**
                 \param lxp what to do with lexeme
                 \param rid rule name
                 \param rrx rule regular expression
                 \param eol is it an end of line?
                 \return new rule
                 */
                template <typename ID, typename RX> static inline
                Rule * New(const LexemeProcess lxp,
                           const ID           &rid,
                           const RX           &rrx,
                           const EndOfLineFlag eol)
                {
                    const Identifier ruleName = rid;
                    const Motif      ruleForm = RegExp::Compile(rrx,0);
                    const unsigned   ruleDeed = DeedFor(lxp,eol);
                    const Identifier ruleInfo = ruleName;
                    const RuleHook   ruleHook = 0;
                    return new Rule(ruleName,ruleForm,ruleDeed,ruleInfo,ruleHook);
                }

                //! creating a rule with a hook
                /**
                 \param lxp what to do with lexeme
                 \param rid rule name
                 \param rrx rule regular expression
                 \param eol is it an end of line?
                 \param objectPointer object pointer
                 \param methodPointer method pointer to call
                 \return new rule
                 */
                template <
                typename ID,
                typename RX,
                typename OBJECT_POINTER,
                typename METHOD_POINTER> static inline
                Rule * New(const LexemeProcess    lxp,
                           const ID           &   rid,
                           const RX           &   rrx,
                           const EndOfLineFlag    eol,
                           OBJECT_POINTER * const objectPointer,
                           METHOD_POINTER   const methodPointer)
                {
                    assert(objectPointer); assert(methodPointer);
                    const Identifier ruleName = rid;
                    const Motif      ruleForm = RegExp::Compile(rrx,0);
                    const unsigned   ruleDeed = DeedFor(lxp,eol) | Hook;
                    const Identifier ruleInfo = ruleName;
                    const RuleHook   ruleHook = new Action(objectPointer,methodPointer);
                    return new Rule(ruleName,ruleForm,ruleDeed,ruleInfo,ruleHook);
                }

                //! creating a 'back' rule without hook
                /**
                 \param lxp what to do with lexeme
                 \param rid rule name
                 \param rrx rule regular expression
                 \param eol is it an end of line?
                 \param objectPointer object pointer
                 \param methodPointer method pointer to call
                 \return new rule
                 */
                template <typename RX> static inline
                Rule * BackFrom(const Identifier   & org,
                                const RX           & brx,
                                const EndOfLineFlag  eol)
                {
                    const Identifier ruleName = new String(BackPrefix,BackLength,org->c_str(), org->size() );
                    const Motif      ruleForm = RegExp::Compile(brx,0);
                    const unsigned   ruleDeed = DeedFor(DropLexeme,eol) | Back;
                    const Identifier ruleInfo = ruleName;
                    const RuleHook   ruleHook = 0;
                    return new Rule(ruleName,ruleForm,ruleDeed,ruleInfo,ruleHook);
                }





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
                RuleHook         hook; //!< optional action
                Rule *           next; //!< for list
                Rule *           prev; //!< for list

            private:
                Y_Disable_Copy_And_Assign(Rule); //!< discarded
            };
        }


    }
}

#endif // !Y_Jive_Lexical_Rule_Included

