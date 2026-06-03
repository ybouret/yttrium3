
#include "y/jive/syntax/rule/terminal.hpp"
#include "y/stream/output.hpp"
#include "y/jive/syntax/xnode.hpp"
#include "y/jive/lexer.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            Terminal:: ~Terminal() noexcept
            {
            }

            static const char *   TermStyle(const Role role,
                                            const Load load) noexcept
            {

                switch(role)
                {
                    case Semantic:
                        switch(load)
                        {
                            case Standard: return "solid,filled";
                            case Univocal: return "solid,filled,rounded";
                        }
                        break;

                    case Dividing:
                        switch(load)
                        {
                            case Standard: return "dashed,filled";
                            case Univocal: return "dashed,filled,rounded";
                        }
                        break;
                }

                return "solid";
            }

            const char * Terminal:: vizStyle() const noexcept
            {
                return TermStyle(role,load);
            }

            OutputStream & Terminal:: vizSelf(OutputStream &fp) const
            {
                nodeName(fp) << '[';
                Label(fp,*name);
                fp << ",shape=box,style=\"" << vizStyle() << "\"";
                return Endl(fp<<']');
            }

            Y_Jive_Syntax_Rule_Impl(Terminal)
            {
                Y_Jive_Syntax("[" << name << "]");
                // pull next lexeme
                Lexeme * const lexeme = framework.get();

                // check if finished
                if(!lexeme)
                {
                    return Outcome(Rejected,Healthy,Blocked);
                }

                // check name
                if( *lexeme->name!= *name)
                {
                    framework.put(lexeme);
                    return Outcome(Rejected,Healthy,Running);
                }

                // grow tree and return accepted
                framework.grow( XNode::Create(*this,lexeme) );
                return Outcome(Accepted,Healthy,Running);
            }

        }

    }

}

