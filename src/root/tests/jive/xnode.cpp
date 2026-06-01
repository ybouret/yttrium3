
#include "y/jive/syntax/xnode.hpp"
#include "y/jive/syntax/rule/terminal.hpp"
#include "y/jive/syntax/rule/inner.hpp"

#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Jive;

namespace
{

}

Y_UTEST(jive_xnode)
{
    Y_SIZEOF(Syntax::XList);
    Y_SIZEOF(Syntax::XNode);
    Y_SIZEOF(Lexeme);

    const Jive::Spot    spot("demo");
    Syntax::Terminal    rterm("INT");
    Jive::Syntax::XNode xterm(rterm,new Jive::Lexeme(spot,"INT") );
    Y_PRINTV(xterm.rule.name);

    Syntax::Inner       rinnr;
    Jive::Syntax::XNode xinnr(rinnr);
    Y_PRINTV(xinnr.rule.name);

    
}
Y_UDONE()

