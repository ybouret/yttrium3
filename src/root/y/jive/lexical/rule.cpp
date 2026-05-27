#include "y/jive/lexical/rule.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            const char   Rule:: BackPrefix[] = "<-";
            const size_t Rule:: BackLength   = sizeof(BackPrefix)-1;

            Rule:: ~Rule() noexcept
            {

            }


            Rule:: Rule(const Identifier & ruleName,
                        const Motif      & ruleForm,
                        const unsigned     ruleDeed,
                        const Identifier & ruleInfo,
                        const RuleHook   & ruleHook) :
            name(ruleName),
            form(ruleForm),
            deed(ruleDeed),
            info(ruleInfo),
            hook(ruleHook),
            next(0),
            prev(0)
            {
                assert(deed&UsedMask);

                if(form->frail())
                    throw Specific::Exception(name->c_str(),"cannot use frail pattern!");
            }


            unsigned Rule:: DeedFor(const LexemeProcess lxp,
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

            unsigned Rule:: DeedForBack(const EndOfLineFlag eol) noexcept
            {
                return DeedFor(DropLexeme,eol) | Back;
            }

            String * Rule:: GetBackName(const Identifier &org)
            {
                return new String(BackPrefix,BackLength,org->c_str(), org->size() );
            }

        }

    }

}

