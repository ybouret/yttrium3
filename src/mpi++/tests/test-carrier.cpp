
#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"
#include <cstring>

using namespace Yttrium;



Y_UTEST(carrier)
{
    MPI & mpi = MPI::Init(&argc,&argv);
    Y_MPI_ForEach(mpi,std::cerr << "@" << mpi << std::endl);

}
Y_UDONE()

