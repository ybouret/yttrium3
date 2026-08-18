

#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(coll)
{
    MPI & mpi = MPI::Init(&argc,&argv);

    int value = 0;
    if(mpi.primary)
        value = 7;
    Y_MPI_ForEach(mpi,std::cerr << mpi << ": value=" << value << std::endl);
    mpi.bcast1(value,0);

    if(mpi.primary)
    {
        std::cerr << std::endl;
    }
    Y_MPI_ForEach(mpi,std::cerr << mpi << ": value=" << value << std::endl);

}
Y_UDONE()

