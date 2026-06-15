#include "y/chemical/weasel.hpp"
#include "y/utest/run.hpp"

#include "y/jive/syntax/grammar.hpp"
#include "y/stream/libc/output.hpp"

using namespace Yttrium;
using namespace Chemical;

Y_UTEST(weasel)
{
    Weasel &   weasel = Weasel::Instance();
    Library    lib;
    Equilibria eqs;

    for(int i=1;i<argc;++i)
    {
        const String data = argv[i];
        weasel(Jive::Module::OpenData(data,data),lib,eqs);
    }

    std::cerr << "lib=" << lib << std::endl;
    std::cerr << "eqs=" << eqs << std::endl;

    {
        OutputFile fp("lib.dot");
        Vizible::Enter(fp);
        for(Library::ConstIterator it=lib->begin();it!=lib->end();++it)
        {
            const Species &sp = **it;
            sp.viz(fp,"blue",0);
        }

        for(Equilibria::ConstIterator it=eqs->begin();it!=eqs->end();++it)
        {
            const Equilibrium &eq = **it;
            eq.vizSelf(fp, "red", 0);
            eq.vizLink(fp, "magenta");
        }

        Vizible::Leave(fp);
    }

    Vizible::DotToPng("lib.dot");


}
Y_UDONE()

