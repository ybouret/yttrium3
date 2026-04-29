#include "y/jive/token.hpp"
#include "y/jive/module.hpp"
#include "y/utest/run.hpp"
#include "y/pointer/auto.hpp"

using namespace Yttrium;

Y_UTEST(jive_source)
{
    Y_SIZEOF(Identifier);
    Y_SIZEOF(Jive::Spot);
    Y_SIZEOF(Jive::Char);
    Y_SIZEOF(Jive::Token);
    Y_SIZEOF(Jive::Module);

    if(argc>1)
    {
        AutoPtr<Jive::Module> m = Jive::Module::OpenFile(argv[1]);
        AutoPtr<Jive::Char>   ch;
        while( (ch = m->get() ).isValid() )
        {
            (std::cerr << **ch).flush();
        }

    }

}
Y_UDONE()

