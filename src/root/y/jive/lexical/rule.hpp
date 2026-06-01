
//! \file

#ifndef Y_Jive_Lexical_Rule_Included
#define Y_Jive_Lexical_Rule_Included 1

#include "y/jive/lexical/action.hpp"
#include "y/jive/regexp.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            //__________________________________________________________________
            //
            //! what to do with found lexeme
            //__________________________________________________________________
            enum LexemeProcess
            {
                EmitLexeme, //!< emit as unit
                DropLexeme  //!< drop
            };

            //__________________________________________________________________
            //
            //! Hook for a rule
            //__________________________________________________________________
            enum EndOfLineFlag
            {
                IsEndOfLine, //!< forwarded to source/module
                NoEndOfLine  //!< [:dot:]
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
                static const unsigned   Emit = 0x01;                     //!< emit lexeme
                static const unsigned   Drop = 0x02;                     //!< drop lexeme
                static const unsigned   Call = 0x04;                     //!< call scanner
                static const unsigned   Back = 0x08;                     //!< back from scanner
                static const unsigned   Jump = 0x10;                     //!< jump to scanner
                static const unsigned   Endl = 0x80;                     //!< propagate endl
                static const unsigned   Mask = Emit|Drop|Call|Back|Jump; //!< alias
                typedef CxxListOf<Rule> List;                            //!< alias
                static const char       BackMarker[];                    //!< "$"
                static const size_t     BackLength;                      //!< strlen(BackPrefix)
                static const char       CallMarker[];                    //!< "@"
                static const size_t     CallLength;                      //!< strlen(CallPrefix)
                static const char       JumpMarker[];                    //!< "=>"
                static const size_t     JumpLength;                      //!< strlen(JumpMarker)

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






                //! creating a rule without hook
                /**
                 \param lxp what to do with lexeme
                 \param rid rule name
                 \param rrx rule regular expression
                 \param eol is it an end of line?
                 \return new rule
                 */
                template <typename ID, typename RX> static inline
                Rule * New(const LexemeProcess  lxp,
                           const ID           & rid,
                           const RX           & rrx,
                           const EndOfLineFlag  eol)
                {
                    const RuleHook   ruleHook = 0;
                    return New_(lxp,rid,rrx,eol,ruleHook);
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
                    const RuleHook   ruleHook = new Action(objectPointer,methodPointer);
                    return New_(lxp,rid,rrx,eol,ruleHook);
                }


                //! creating a 'back' rule without hook
                /**
                 \param org current scanner name
                 \param brx rule regular expression
                 \param eol is it an end of line?
                 \return new rule
                 */
                template <typename RX> static inline
                Rule * BackFrom(const Identifier   & org,
                                const RX           & brx,
                                const EndOfLineFlag  eol)
                {
                    const RuleHook   ruleHook = 0;
                    return BackFrom_(org,brx,eol,ruleHook);
                }

                //! creating a 'back' rule with a hook
                /**
                 \param org current scanner name
                 \param brx rule regular expression
                 \param eol is it an end of line?
                 \param objectPointer object pointer
                 \param methodPointer method pointer to invoke
                 \return new rule
                 */
                template <typename RX,
                typename OBJECT_POINTER,
                typename METHOD_POINTER> static inline
                Rule * BackFrom(const Identifier   &   org,
                                const RX           &   brx,
                                const EndOfLineFlag    eol,
                                OBJECT_POINTER * const objectPointer,
                                METHOD_POINTER   const methodPointer)
                {
                    const RuleHook   ruleHook = new Action(objectPointer,methodPointer);
                    return BackFrom_(org,brx,eol,ruleHook);
                }

                //! creating a 'call' rule without hook
                /**
                 \param src source scanner's name
                 \param tgt target scanner's name
                 \param grx goto regular expression
                 \return new rule
                 */
                template <typename SRC, typename TGT, typename GRX> static inline
                Rule *MakeCall(const SRC          & src,
                               const TGT          & tgt,
                               const GRX          & grx)
                {
                    const RuleHook rcb = 0;
                    return GoTo_(src,tgt,grx,false,rcb);
                }


                //! creating a 'call' rule with a hook
                /**
                 \param src           source scanner's name
                 \param tgt           target scanner's name
                 \param grx           goto regular expression
                 \param objectPointer object pointer
                 \param methodPointer method pointer to invoke
                 \return new rule
                 */
                template <
                typename SRC,
                typename TGT,
                typename GRX,
                typename OBJECT_POINTER,
                typename METHOD_POINTER> static inline
                Rule *MakeCall(const SRC          & src,
                               const TGT          & tgt,
                               const GRX          & grx,
                               OBJECT_POINTER * const objectPointer,
                               METHOD_POINTER   const methodPointer)
                {
                    const RuleHook rcb = new Action(objectPointer,methodPointer);
                    return GoTo_(src,tgt,grx,false,rcb);
                }


                //! creating a 'jump' rule without hook
                /**
                 \param src source scanner's name
                 \param tgt target scanner's name
                 \param grx goto regular expression
                 \return new rule
                 */
                template <typename SRC, typename TGT, typename GRX> static inline
                Rule *MakeJump(const SRC          & src,
                               const TGT          & tgt,
                               const GRX          & grx)
                {
                    const RuleHook rcb = 0;
                    return GoTo_(src,tgt,grx,true,rcb);
                }

                //! creating a 'jump' rule with a hook
                /**
                 \param src           source scanner's name
                 \param tgt           target scanner's name
                 \param grx           goto regular expression
                 \param objectPointer object pointer
                 \param methodPointer method pointer to invoke
                 \return new rule
                 */
                template <
                typename SRC,
                typename TGT,
                typename GRX,
                typename OBJECT_POINTER,
                typename METHOD_POINTER> static inline
                Rule *MakeJump(const SRC          & src,
                               const TGT          & tgt,
                               const GRX          & grx,
                               OBJECT_POINTER * const objectPointer,
                               METHOD_POINTER   const methodPointer)
                {
                    const RuleHook rcb = new Action(objectPointer,methodPointer);
                    return GoTo_(src,tgt,grx,true,rcb);
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

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
                Y_Disable_Copy_And_Assign(Rule);
                static unsigned DeedFor(const LexemeProcess,const EndOfLineFlag) noexcept;
                static unsigned DeedForBack(const EndOfLineFlag) noexcept;
                static String * GetBackName(const Identifier &);
                static String * GetGoToName(const Identifier &, const bool, const Identifier &);

                template <typename ID, typename RX> static inline
                Rule * New_(const LexemeProcess lxp,
                            const ID           &rid,
                            const RX           &rrx,
                            const EndOfLineFlag eol,
                            const RuleHook     &ruleHook)
                {
                    const Identifier ruleName = rid;
                    const Motif      ruleForm = RegExp::Compile(rrx,0);
                    const unsigned   ruleDeed = DeedFor(lxp,eol);
                    const Identifier ruleInfo = ruleName;
                    return new Rule(ruleName,ruleForm,ruleDeed,ruleInfo,ruleHook);
                }

                //! creating a 'go to'
                /**

                 \return new rule
                 */
                template <typename SRC, typename TGT, typename GRX> static inline
                Rule * GoTo_(const SRC          & src,
                             const TGT          & tgt,
                             const GRX          & grx,
                             const bool           jmp,
                             const RuleHook     & rcb)
                {
                    const Identifier _original = src;
                    const Identifier _ruleInfo = tgt;
                    const Identifier _ruleName = GetGoToName(_original,jmp,_ruleInfo);
                    const Motif      _ruleForm = RegExp::Compile(grx,0);
                    const unsigned   _ruleDeed = jmp ? Jump : Call;
                    return new Rule(_ruleName,_ruleForm,_ruleDeed,_ruleInfo,rcb);
                }

                template <typename RX> static inline
                Rule * BackFrom_(const Identifier   & org,
                                 const RX           & brx,
                                 const EndOfLineFlag  eol,
                                 const RuleHook &     ruleHook)
                {
                    const Identifier ruleName = GetBackName(org);
                    const Motif      ruleForm = RegExp::Compile(brx,0);
                    const unsigned   ruleDeed = DeedForBack(eol);
                    const Identifier ruleInfo = ruleName;
                    return new Rule(ruleName,ruleForm,ruleDeed,ruleInfo,ruleHook);
                }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
            };
        }


    }
}

#endif // !Y_Jive_Lexical_Rule_Included

