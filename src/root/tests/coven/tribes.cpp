
#include "y/coven/tribes.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(coven_tribes)
{
    Core::Rand    ran;

    const size_t nr = 5;
    const size_t nc = 4;

    Coven::RowCache rc;
    {
        Matrix<int>     mu(nr,nc);
        Coven::Metrics  metrics(nc);
        Coven::VCache   vc(metrics);

        Coven::Tribes tribes(mu,vc,rc);
        //tribes.writeXML(std::cerr);

        apn num = tribes->size;
        std::cerr << "num=" << num << " / " << apn::Arrange(nr,1) << std::endl;
        while(true)
        {
            const size_t gen = tribes.generate(mu);
            //tribes.writeXML(std::cerr);
            if(gen<=0) break;
            std::cerr << "gen=" << gen << " / " << apn::Arrange(nr,tribes.hired) << std::endl;
            num += gen;
        }

        std::cerr << "#generated=" << num << std::endl;



    }


}
Y_UDONE()
