
#include "y/chemical/weasel.hpp"
#include "y/chemical/reactive/equilibrium/aftermath.hpp"
#include "y/utest/run.hpp"

#include "y/container/cxx/array.hpp"

#include "y/chemical/type/concentration.hpp"
#include "y/random/park-miller.hpp"
#include "y/core/display.hpp"
#include "y/string/env/convert.hpp"

using namespace Yttrium;
using namespace Chemical;

Y_UTEST(aftermath)
{
    Random::ParkMiller ran;
    Weasel &           weasel = Weasel::Instance();
    Library            lib;
    Equilibria         eqs;

    for(int i=1;i<argc;++i)
    {
        const String data = argv[i];
        weasel(Jive::Module::OpenData(data,data),lib,eqs);
    }

    std::cerr << "-- aftermath for:" << std::endl;
    std::cerr << "lib=" << lib << std::endl;
    std::cerr << "eqs=" << eqs << std::endl;

    const size_t M = lib->size();
    CxxArray<xreal_t> C0(M,0.0);
    CxxArray<xreal_t> Ceq(M,0.0);
    XMul              xmul;
    XAdd              xadd;

    const double probaZ = EnvironmentConvert::To<double>("probaZ",0);
    Concentration::Fill(ran,C0,M,probaZ);

    Core::Display(std::cerr << "C0=", C0.begin(), C0.size(), xreal_t::ToString) << std::endl;

    for(Equilibria::Iterator it=eqs.begin();it!=eqs.end();++it)
    {
        Equilibrium &eq = **it;
        const xreal_t eK = eq.K(0);
        Aftermath     am = Aftermath::Compute(Ceq,C0,eq,eK,TopLevel,xmul,xadd);
    }

}
Y_UDONE()

