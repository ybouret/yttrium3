//! \file

#ifndef Y_Jive_Lexical_Scanner_Included
#define Y_Jive_Lexical_Scanner_Included 1

#include "y/jive/lexical/unit.hpp"
#include "y/jive/lexical/rule.hpp"
#include "y/jive/lexical/command.hpp"
#include "y/jive/regexp.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            //__________________________________________________________________
            //
            //! End Of Stream Policy
            //__________________________________________________________________
            enum OnEOS
            {
                AcceptEOS, //!< scanner is ok to quit
                RejectEOS  //!< scanner is not done!
            };


            //__________________________________________________________________
            //
            //
            //
            //! Produce units with a set of rules
            //
            //
            //__________________________________________________________________
            class Scanner : public CountedObject
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                class Code;

                //! setup \param sid name \param eos End Of Stream policy
                template <typename SID> inline
                explicit Scanner(const SID &sid, const OnEOS eos = AcceptEOS) :
                name(sid),
                code( CreateCode(sid) ),
                onEOS(eos)
                {

                }

                //! cleanup
                virtual ~Scanner() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                const String & key() const noexcept; //!< \return *name
                const Rule   & add(Rule * const);    //!< add newly created rule \return persistent reference

                //! probe next Unit
                /**
                 \param source  source to probe
                 \param command modified upon control lexeme
                 \return 0 if EOS or control lexeme, a new unit otherwise
                 */
                Unit *probe(Source &source, Command &command);


                //______________________________________________________________
                //
                //
                // API
                //
                //______________________________________________________________

                //! emit a lexeme
                /**
                 \param id rule/lexeme name
                 \param rx regular expression
                 \return created rule
                 */
                template <typename ID, typename RX> inline
                const Rule & emit(const ID &id, const RX &rx)
                {
                    return add( Rule::New(EmitLexeme,id,rx,NoEndOfLine) );
                }

                //! emit a lexeme with hook
                /**
                 \param id rule/lexeme name
                 \param rx regular expression
                 \param host object address
                 \param meth object method to call
                 \return created rule
                 */
                template <
                typename ID,
                typename RX,
                typename OBJECT_POINTER,
                typename METHOD_POINTER>
                inline
                const Rule & emit(const ID &id, const RX &rx, OBJECT_POINTER * const host, METHOD_POINTER const meth)
                {
                    return add( Rule::New(EmitLexeme,id,rx,NoEndOfLine,host,meth) );
                }



                //! drop a lexeme
                /**
                 \param id rule/lexeme name
                 \param rx regular expression
                 \return created rule
                 */
                template <typename ID, typename RX> inline
                const Rule & drop(const ID &id, const RX &rx)
                {
                    return add( Rule::New(DropLexeme,id,rx,NoEndOfLine) );
                }

                //! drop a lexeme with hook
                /**
                 \param id rule/lexeme name
                 \param rx regular expression
                 \param host object address
                 \param meth object method to call
                 \return created rule
                 */
                template <
                typename ID,
                typename RX,
                typename OBJECT_POINTER,
                typename METHOD_POINTER>
                inline
                const Rule & drop(const ID &id, const RX &rx, OBJECT_POINTER * const host, METHOD_POINTER const meth)
                {
                    return add( Rule::New(DropLexeme,id,rx,NoEndOfLine,host,meth) );
                }




                //! end-of-line lexeme
                /**
                 \param id  rule/lexeme name
                 \param rx  regular expression
                 \param lxp default is DropLexeme, use EmitLexeme if necessary
                 \return created rule
                 */
                template <typename ID, typename RX> inline
                const Rule & endl(const ID &id, const RX &rx, const LexemeProcess lxp = DropLexeme )
                {
                    return add( Rule::New(lxp,id,rx,IsEndOfLine) );
                }

#if 0
                template <typename ID> inline
                const Rule & call(const ID &id, const Motif &spark)
                {
                    const Identifier _dest(id);
                    const String     _call = *name + "->" + *_dest;
                    const Identifier _name(_call);
                    return add( new Rule(_name,spark,Rule::Call,_dest,0) );
                }
#endif

                template <typename RX> inline
                const Rule & back(const RX &brx, const EndOfLineFlag eol)
                {
                    return add( Rule::BackFrom(name,brx,eol) );
                }


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Identifier name; //!< identifier
            private:
                Code * const     code; //!< inner code
            public:
                const OnEOS      onEOS; //!< End Of Stream policy

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            private:
                Y_Disable_Copy_And_Assign(Scanner);
                static Code * CreateCode(const Identifier &);
                const Rule &  processing(const Identifier &, const Motif &, const unsigned);
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
            };
        }

    }

}

#endif // !Y_Jive_Lexical_Scanner_Included

