


#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/random/fill.hpp"
#include "y/format/human-readable.hpp"

#include <cstring>

using namespace Yttrium;

Y_UTEST(p2p)
{
    System::WallTime chrono;
    MPI & mpi = MPI::Init(&argc,&argv);

    Y_MPI_Trace(mpi, std::cerr << "Testing ping..." << std::endl; );
    {
        char buffer[128];

        for(size_t iter=0;iter<16;++iter)
        {
            if(mpi.primary)
            {
                Core::Rand ran;
                Random::FillWith(ran,buffer,sizeof(buffer));

                for(size_t rank=1;rank<mpi.size;++rank)
                {
                    mpi.sendBytes(buffer,sizeof(buffer),rank);
                }
            }
            else
            {
                memset(buffer,0,sizeof(buffer));
                mpi.recvBytes(buffer,sizeof(buffer),0);
            }

        }

        Y_MPI_ForEach(mpi,std::cerr
                      << "send: "    << std::setw(10) << mpi.sendRate.bytes << "@" << mpi.sendRate.hrt(chrono)
                      << " | recv: " << std::setw(10) << mpi.recvRate.bytes << "@" << mpi.recvRate.hrt(chrono) << std::endl;);
    }

    mpi.resetRates();

    {
        char here[32];
        char peer[sizeof(here)];
        mpi.sendrecvBytes(here, sizeof(here), mpi.nextRank(), peer, sizeof(peer), mpi.prevRank());
    }

}
Y_UDONE()

