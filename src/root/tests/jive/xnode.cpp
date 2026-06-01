
#include "y/jive/syntax/xnode.hpp"
#include "y/jive/syntax/rules/terminal.hpp"
#include "y/jive/syntax/rules/inner.hpp"

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

#if 0
    Jive::Syntax::XNode xterm( new Jive::Lexeme(spot,"ID") );
    Y_PRINTV(xterm.name);
    Jive::Syntax::XNode xintr(spot.title);
    Y_PRINTV(xintr.name);
#endif

}
Y_UDONE()

