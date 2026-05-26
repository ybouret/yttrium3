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
                    const  Identifier _name(id);
                    const  Motif      _form( RegExp::Compile(rx,0) );
                    return processing(_name,_form,Rule::Emit);
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
                    const  Identifier _name(id);
                    const  Motif      _form( RegExp::Compile(rx,0) );
                    return processing(_name,_form,Rule::Drop);
                }

                
                //! end-of-line lexeme
                /**
                 \param id rule/lexeme name
                 \param rx regular expression
                 \param doEmit if necessary, default is false
                 \return created rule
                 */
                template <typename ID, typename RX> inline
                const Rule & endl(const ID &id, const RX &rx, const bool doEmit = false)
                {
                    const  Identifier _name(id);
                    const  Motif      _form( RegExp::Compile(rx,0) );
                    return processing(_name,_form,(doEmit ? Rule::Emit :Rule::Drop)|Rule::Endl);
                }


                template <typename ID> inline
                const Rule & call(const ID &id, const Motif &spark)
                {
                    const Identifier _dest(id);
                    const String     _call = *name + "->" + *_dest;
                    const Identifier _name(_call);
                    return add( new Rule(_name,spark,Rule::Call,_dest,0) );
                }


                template <typename RX> inline
                const Rule & back(const RX &rx, const bool newLine = false)
                {
                    const String     _back = "<-" + *name;
                    const Identifier _name(_back);
                    const  Motif     _form( RegExp::Compile(rx,0) );
                    return add( new Rule(_name,_form,Rule::Back | (newLine ? Rule::Endl : 0),_name,0) );
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

