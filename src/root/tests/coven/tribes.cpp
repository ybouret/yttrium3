
#include "y/coven/tribes.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(coven_tribes)
{
    Core::Rand    ran;

    const size_t nr = 3;
    const size_t nc = 4;

    Coven::RowCache rc;
    {
        Matrix<int>     mu(nr,nc);
        Coven::Metrics  metrics(nc);
        Coven::VCache   vc(metrics);

        Coven::Tribes tribes(mu,vc,rc);

        for(const Coven::Tribe *tribe=tribes->head;tribe;tribe=tribe->next)
        {
            std::cerr << "hired=" << tribe->hired << " | ready=" << tribe->ready << std::endl;

        }


    }


}
Y_UDONE()
