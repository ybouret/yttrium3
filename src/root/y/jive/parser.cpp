
#include "y/jive/parser.hpp"
#include "y/exception.hpp"
#include "y/jive/pattern/basic/byte.hpp"
#include "y/jive/syntax/rule/compound.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Parser:: ~Parser() noexcept
        {

        }

        const Syntax::Rule & Parser:: mark(const char c)
        {
            const String                ruleName(c);
            const Syntax::Rule  * const xRule = querySyntaxRule(ruleName);
            const Lexical::Rule * const lRule = queryLexicalRule(ruleName);
            if(xRule)
            {
                if(xRule->isInternal())           throw Specific::Exception(lang->c_str(),"[%s] is not a terminal!",          ruleName.c_str());
                if(!lRule)                        throw Specific::Exception(lang->c_str(),"[%s] has not lexical definition!", ruleName.c_str());
                if(lRule->form->uuid!=Byte::UUID) throw Specific::Exception(lang->c_str(),"[%s] is not a single char!",       ruleName.c_str());
                return *xRule;
            }
            else
            {
                if(lRule) throw Specific::Exception(lang->c_str(),"[%s] has not syntax definition!",ruleName.c_str());
                return mark(c,c);
            }
        }

        const Syntax::Terminal & Parser:: term(const char c)
        {
            return term(c,c);
        }


        const Syntax::Rule & Parser:: eponymous(const String &ruleName)
        {
            const Syntax::Rule  * const xRule = querySyntaxRule(ruleName);
            const Lexical::Rule * const lRule = queryLexicalRule(ruleName);
            const Terminal      *       t     = 0;

            // query or build terminal
            if(xRule)
            {
                if(xRule->isInternal()) throw Specific::Exception(lang->c_str(),"[%s] is not a terminal!",          ruleName.c_str());
                if(!lRule)                        throw Specific::Exception(lang->c_str(),"[%s] has not lexical definition!", ruleName.c_str());
                t = dynamic_cast<const Terminal *>(xRule);
            }
            else
            {
                if(lRule) throw Specific::Exception(lang->c_str(),"[%s] has not syntax definition!",ruleName.c_str());
                t =  &term(ruleName,ruleName);
            }

            assert(0!=t);
            if(t->load != Syntax::Univocal) throw Specific::Exception(lang->c_str(),"[%s] is not univocal!", ruleName.c_str());
            
            return *t;
        }


        const Syntax::Rule & Parser:: extra(const char separator, const Rule &rule)
        {
            return zom( cat( mark(separator), rule) );
        }

        const Syntax::Rule & Parser:: parens(const Rule &rule)
        {
            return cat( mark('('), rule, mark(')'));
        }



        namespace Syntax
        {
            Compound & Compound:: operator<<(const char c)
            {
                if(!parser) throw Specific::Exception(name->c_str(),"not linked to parser to create mark!!");
                pushTail( parser->mark(c) );
                return *this;
            }

            Compound & Compound:: operator<< (const String &ruleName)
            {
                if(!parser) throw Specific::Exception(name->c_str(),"not linked to parser to create eponymous terminal!!");
                pushTail( parser->eponymous(ruleName) );
                return *this;
            }

            Compound & Compound:: operator<<(const char * const ruleName)
            {
                const String _(ruleName);
                return *this << _;
            }
        }


        Syntax::XNode * Parser:: getAST(Module * const m)
        {
            Source source(m);
            reset();
            return run(*this,source);
        }

        Parser * Parser:: myself() noexcept { return this; }


    }

}

