#include "y/chemical/weasel.hpp"
#include "y/utest/run.hpp"
#include "y/chemical/formula/translator.hpp"

#include "y/jive/syntax/grammar.hpp"

using namespace Yttrium;
using namespace Chemical;

Y_UTEST(weasel)
{
    Weasel & weasel            = Weasel::Instance();
    weasel.formulaTranslator.verbose = true;
    Library  lib;

    //Jive::Syntax::Rule::Verbose = true;

    if(argc>1)
    {
        weasel(Jive::Module::OpenFile(argv[1]),lib);
    }

    std::cerr << "lib=" << lib << std::endl;

}
Y_UDONE()

