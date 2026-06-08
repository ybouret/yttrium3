
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

        const Syntax::Rule & Parser:: extra(const char separator, const Rule &rule)
        {
            return zom( cat( mark(separator), rule) );
        }


        namespace Syntax
        {
            Compound & Compound:: operator<<(const char c)
            {
                if(!parser) throw Specific::Exception(name->c_str(),"not linked to parser!!");
                pushTail( parser->mark(c) );
                return *this;
            }
        }
    }

}

