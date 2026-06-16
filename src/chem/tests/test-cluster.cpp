
#include "y/chemical/weasel.hpp"
#include "y/utest/run.hpp"

#include "y/stream/libc/output.hpp"
#include "y/chemical/reactive/equilibrium/partition.hpp"
#include "y/chemical/plexus/warden.hpp"



using namespace Yttrium;
using namespace Chemical;

Y_UTEST(cluster)
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

    bool      verbose = true;
    XML::Log  xml(std::cerr,verbose);
    Partition part(xml,eqs);

    for(const EGroup *g=part.party.head;g;g=g->next)
    {
        Topology topo(xml,*g);
        Canon    canon(xml,topo);
        Warden   warden(xml,canon);
    }



}
Y_UDONE()

