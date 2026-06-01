
#include "y/jive/syntax/xnode.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(jive_xnode)
{
    Y_SIZEOF(Jive::Syntax::XList);
    Y_SIZEOF(Jive::Syntax::XNode);
    Y_SIZEOF(Jive::Lexeme);

    const Jive::Spot    spot("demo");
    Jive::Syntax::XNode xterm( new Jive::Lexeme(spot,"ID") );
    Y_PRINTV(xterm.name);
    Jive::Syntax::XNode xintr(spot.title);
    Y_PRINTV(xintr.name);


}
Y_UDONE()

