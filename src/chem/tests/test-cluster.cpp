
#include "y/chemical/weasel.hpp"
#include "y/utest/run.hpp"

#include "y/stream/libc/output.hpp"
#include "y/chemical/reactive/equilibrium/partition.hpp"
#include "y/chemical/plexus/conservation/canons.hpp"
#include "y/chemical/plexus/warden.hpp"
#include "y/chemical/plexus/combinatorics.hpp"
#include "y/container/sequence/vector.hpp"


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

    Vector<xreal_t> K;

    for(const EGroup *g=part.party.head;g;g=g->next)
    {
        Topology             topo(xml,*g);
        Conservations        conservations(xml,topo);
        Conservation::Canons canons(xml,conservations.laws,conservations.lfmt);
        continue;
        Warden               warden(xml,conservations);
        Combinatorics        combinatorics(xml,topo,eqs,K);
    }

    std::cerr << std::endl;
    Y_SIZEOF(Topology);
    Y_SIZEOF(Conservations);
    Y_SIZEOF(Warden);

    Y_SIZEOF(Roll<Species>);
    Y_SIZEOF(Roll<Equilibrium>);

    std::cerr << "lib=" << lib << std::endl;


}
Y_UDONE()

