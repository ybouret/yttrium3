#include "y/jive/lexical/rule.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            const char   Rule:: BackMarker[] = "$";
            const size_t Rule:: BackLength   = sizeof(BackMarker)-1;

            const char   Rule:: CallMarker[] = "@";
            const size_t Rule:: CallLength   = sizeof(CallMarker)-1;

            const char   Rule:: JumpMarker[] = "=>";
            const size_t Rule:: JumpLength   = sizeof(JumpMarker)-1;

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
                switch(deed&Mask)
                {
                    case Emit:
                    case Drop:
                    case Call:
                    case Jump:
                    case Back:
                        break;
                    default:
                        throw Specific::Exception(name->c_str(),"invalid deed=0x%x",deed);
                }

                if(form->frail())
                    throw Specific::Exception(name->c_str(),"cannot use frail pattern!");
            }


            unsigned Rule:: DeedFor(const LexemeProcess lxp,
                                    const EndOfLineFlag eol) noexcept
            {
                unsigned ruleDeed = 0;
                switch(lxp)
                {
                    case EmitLexeme: ruleDeed = Emit; break;
                    case DropLexeme: ruleDeed = Drop; break;
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
                unsigned ruleDeed = Back;
                switch(eol)
                {
                    case IsEndOfLine: ruleDeed |= Endl; break;
                    case NoEndOfLine:                   break;
                }
                return ruleDeed;
            }

            String * Rule:: GetBackName(const Identifier &org)
            {
                return new String(org->c_str(), org->size(),BackMarker,BackLength);
            }

            String * Rule:: GetGoToName(const Identifier &from, const bool jmp, const Identifier &to)
            {
                return jmp ?
                new String(from->c_str(),from->size(),JumpMarker,JumpLength,to->c_str(),to->size()) :
                new String(from->c_str(),from->size(),CallMarker,CallLength,to->c_str(),to->size());
            }



        }

    }

}

