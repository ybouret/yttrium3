
#include "y/chemical/weasel.hpp"
#include "y/utest/run.hpp"

#include "y/stream/libc/output.hpp"

#include "y/chemical/plexus/clusters.hpp"

#include "y/chemical/plexus/conservation/adjudicator.hpp"

 #include "y/container/cxx/array.hpp"
#include "y/string/env/convert.hpp"
#include "y/random/park-miller.hpp"

#include "y/mkl/algebra/xgj.hpp"
#include "y/string/format.hpp"
#include "y/jive/vfs.hpp"
#include "y/vfs/local/fs.hpp"

using namespace Yttrium;
using namespace Chemical;

Y_UTEST(cluster)
{
    VFS &              fs     = LocalFS::Instance();
    Weasel &           weasel = Weasel::Instance();
    Library            lib;
    Equilibria         eqs;
    Random::ParkMiller ran;

    for(int i=1;i<argc;++i)
    {
        const String data = argv[i];
        weasel(Jive::Module::OpenData(data,data),lib,eqs);
    }

    std::cerr << "lib=" << lib << std::endl;
    std::cerr << "eqs=" << eqs << std::endl;


    bool      verbose = true;
    XML::Log  xml(std::cerr,verbose);
    Clusters  cls(xml,eqs);
    std::cerr << std::endl;


    Jive::_VFS::Apply(fs, ".", "cs[:digit:][.]png", Jive::Matching::Exactly, VFS::Entry::Base, Jive::_VFS::Remove);

    cls.renderAll("cs");





#if 0
    const Partition part(xml,eqs);

    Vector<xreal_t>   K;
    const size_t      M = lib->size();
    CxxArray<xreal_t> C(M);
    const double probaZ = EnvironmentConvert::To<double>("probaZ",0);
    const double probaN = EnvironmentConvert::To<double>("probaN",0);
    Concentration::Fill(ran,C,M,probaZ,probaN);

    for(const EGroup *g=part.party.head;g;g=g->next)
    {
        Topology             topo(xml,*g);
        Conservations        conservations(xml,topo);
        Conservation::Canons canons(xml,conservations.laws,topo,conservations.lfmt);

        for(const Conservation::Canon *canon=canons->head;canon;canon=canon->next)
        {
            Conservation::Adjudicator adjudicator(*canon);
            adjudicator.judge(xml,C,TopLevel);
        }

        Combinatorics        combinatorics(xml,topo,eqs,K);
    }

    std::cerr << std::endl;
    std::cerr << "lib=" << lib << std::endl;
#endif



}
Y_UDONE()

