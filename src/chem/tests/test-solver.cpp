

#include "y/chemical/weasel.hpp"
#include "y/utest/run.hpp"

#include "y/stream/libc/output.hpp"

#include "y/chemical/plexus/clusters.hpp"

#include "y/container/cxx/array.hpp"
#include "y/string/env/convert.hpp"
#include "y/random/park-miller.hpp"

#include "y/mkl/algebra/xgj.hpp"
#include "y/string/format.hpp"

#include "y/vfs/local/fs.hpp"
#include "y/jive/vfs.hpp"

#include "y/chemical/plexus/solver.hpp"
#include "y/chemical/type/concentration.hpp"



using namespace Yttrium;
using namespace Chemical;

Y_UTEST(solver)
{
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

    Jive::_VFS::Apply( LocalFS::Instance(), ".", "cs[:digit:][.]png", Jive::Matching::Exactly, VFS::Entry::Base, Jive::_VFS::Remove);
    cls.renderAll("cs");

    const size_t      M = lib->size();
    CxxArray<xreal_t> C(M);
    const double      probaZ = EnvironmentConvert::To<double>("probaZ",0);
    const double      probaN = EnvironmentConvert::To<double>("probaN",0);
    Concentration::Fill(ran,C,M,probaZ,probaN);

    for(const Cluster *cl=cls->head;cl;cl=cl->next)
    {
        Solver solver(*cl);
        solver.run(xml,C,TopLevel,cls.K);
    }


}
Y_UDONE()

