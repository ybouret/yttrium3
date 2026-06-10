//! \file

#ifndef Y_Jive_Parser_Included
#define Y_Jive_Parser_Included 1

#include "y/jive/lexer.hpp"
#include "y/jive/syntax/grammar.hpp"

namespace Yttrium
{
    namespace Jive
    {
        //______________________________________________________________________
        //
        //
        //
        //! Parser
        //
        //
        //______________________________________________________________________
        class Parser : public Lexer, public Syntax::Grammar
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Syntax::Terminal Terminal; //!< echo
            typedef Syntax::Compound Compound; //!< echo


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param id for lexer name and grammar language
            template <typename ID> inline
            explicit Parser(const ID &id) : Lexer(id), Syntax::Grammar(name,this)
            {
            }

            //! cleanup
            virtual ~Parser() noexcept;


            //__________________________________________________________________
            //
            //
            // API for terminals
            //
            //__________________________________________________________________

            //! setup semantic terminal
            /**
             \param id terminal name
             \param rx terminal regular expression
             \return created terminal
             */
            template <typename ID, typename RX> inline
            const Terminal &term(const ID &id, const RX &rx) {
                return term_(id,rx,Syntax::Semantic);
            }


            const Rule &term(const char); //!< \return term as single char

            //! setup dividing terminal
            /**
             \param id terminal name
             \param rx terminal regular expression
             \return created terminal
             */
            template <typename ID, typename RX> inline
            const Terminal &mark(const ID &id, const RX &rx) {
                return term_(id,rx,Syntax::Dividing);
            }

            const Rule & mark(const char);                //!< \return on-the-fly mark
            const Rule & eponymous(const String &);       //!< \return on the fly UNIVOCAL eponymous terminal
            const Rule & extra(const char, const Rule &); //!< \return zom( cat(separator,rule) )
            const Rule & parens(const Rule &);            //!< \return grp( '(', rule , ')' )

            //! create a terminal from and advanced plugin
            /**
             \param hint plugin selector
             \param pid  terminal name from pligin
             \return created terminal
             */
            template <typename ID, typename PLUGIN> inline
            const Terminal & use(const TypeToType<PLUGIN> hint, const ID &pid)
            {
                const Lexical::Rule & plg = dial(hint,pid);
                return trm(plg.info,Syntax::Semantic,Syntax::Standard);
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            XNode * getAST(Module * const);



        private:
            Y_Disable_Copy_And_Assign(Parser); //!< discarded

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            template <typename ID, typename RX> inline
            const Terminal & term_(const ID &id, const RX &rx, const Syntax::Role ruleRole )
            {
                const Lexical::Rule & lexicalRule = emit(id,rx);
                const Syntax::Load    ruleLoad    = lexicalRule.form->univocal() ? Syntax::Univocal : Syntax::Standard;
                return trm(lexicalRule.name,ruleRole,ruleLoad);
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };
    }
}

#endif // !Y_Jive_Parser_Included

