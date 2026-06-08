//! \file

#ifndef Y_Jive_Parser_Included
#define Y_Jive_Parser_Included 1

#include "y/jive/lexer.hpp"
#include "y/jive/syntax/grammar.hpp"

namespace Yttrium
{
    namespace Jive
    {
        class Parser : public Lexer, public Syntax::Grammar
        {
        public:
            typedef Syntax::Terminal Terminal;

            template <typename ID> inline
            explicit Parser(const ID &id) : Lexer(id), Syntax::Grammar(name,this)
            {
            }

            template <typename ID, typename RX> inline
            const Terminal &term(const ID &id, const RX &rx) {
                return term_(id,rx,Syntax::Semantic);
            }

            template <typename ID, typename RX> inline
            const Terminal &mark(const ID &id, const RX &rx) {
                return term_(id,rx,Syntax::Dividing);
            }

            const Rule & mark(const char);
            const Rule & eponymous(const String &);
            const Rule & extra(const char, const Rule &);


            virtual ~Parser() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Parser);

            template <typename ID, typename RX> inline
            const Terminal & term_(const ID &id, const RX &rx, const Syntax::Role ruleRole )
            {
                const Lexical::Rule & lexicalRule = emit(id,rx);
                const Syntax::Load    ruleLoad    = lexicalRule.form->univocal() ? Syntax::Univocal : Syntax::Standard;
                return trm(id,ruleRole,ruleLoad);
            }
        };
    }
}

#endif // !Y_Jive_Parser_Included

