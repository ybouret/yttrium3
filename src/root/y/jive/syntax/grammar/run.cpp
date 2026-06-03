
#include "y/jive/syntax/grammar/core.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            XNode * CoreGrammar:: run(Lexer &lexer, Source &source) const
            {
                assert(rules.size>0);
                Framework      framework(lexer,source);
                const Rule &   rule    = *rules.head;
                const Outcome  outcome = rule.accepts(framework);
                switch(outcome.result)
                {
                    case Accepted:
                        std::cerr << "Accepted!" << std::endl;
                        break;

                    case Rejected:
                        std::cerr << "Rejected!" << std::endl;
                        return 0;
                }

                if(!framework.ok())
                {
                    std::cerr << "produced empty tree!" << std::endl;
                    return 0;
                }

                AutoPtr<XNode> tree = framework.pop();
                Vizible::Render("tree.dot",*tree,true);
                return 0;
            }
        }

    }

}

