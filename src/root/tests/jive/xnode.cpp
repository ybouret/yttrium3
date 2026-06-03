
#include "y/jive/syntax/xnode.hpp"
#include "y/jive/syntax/rule/terminal.hpp"
#include "y/jive/syntax/rule/inner.hpp"
#include "y/format/hexadecimal.hpp"

#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Jive;

#define PRINTH(FIELD) do { const unsigned f = (FIELD); std::cerr << #FIELD << " = " << Hexadecimal(f) << std::endl; } while(false)

Y_UTEST(jive_xnode)
{
    Y_SIZEOF(Syntax::XList);
    Y_SIZEOF(Syntax::XNode);
    Y_SIZEOF(Lexeme);

    const Jive::Spot       spot("demo");
    Syntax::Terminal       rterm("INT");
    AutoPtr<Syntax::XNode> xterm = Syntax::XNode::Create(rterm,new Jive::Lexeme(spot,"INT") );
    Y_PRINTV(xterm->rule.name);

    Syntax::Inner          rinnr;
    AutoPtr<Syntax::XNode> xinnr = Syntax::XNode::Create(rinnr);
    Y_PRINTV(xinnr->rule.name);

    PRINTH(Syntax::Outcome::Accepted);
    PRINTH(Syntax::Outcome::Rejected);
    PRINTH(Syntax::Outcome::Weakened);
    PRINTH(Syntax::Outcome::Finished);
    PRINTH(Syntax::Outcome::Modifier);
    PRINTH(Syntax::Outcome::Answered);


}
Y_UDONE()

