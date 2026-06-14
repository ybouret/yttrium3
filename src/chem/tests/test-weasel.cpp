#include "y/chemical/weasel.hpp"
#include "y/utest/run.hpp"

#include "y/jive/syntax/grammar.hpp"

using namespace Yttrium;
using namespace Chemical;

Y_UTEST(weasel)
{
    Weasel &   weasel = Weasel::Instance();
    Library    lib;
    Equilibria eqs;

    if(argc>1)
    {
        weasel(Jive::Module::OpenFile(argv[1]),lib,eqs);
    }

    std::cerr << "lib=" << lib << std::endl;

}
Y_UDONE()

