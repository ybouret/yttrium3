
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

using namespace Yttrium;
using namespace Chemical;

Y_UTEST(cluster)
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
    std::cerr << std::endl;


    cls.renderAll("cs");

}
Y_UDONE()

