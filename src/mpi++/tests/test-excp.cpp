#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(excp)
{
    try {
        throw MPI::Exception(MPI_ERR_IO, "test from %s", test);
    }
    catch(const Exception &excp)
    {
        excp.display(std::cerr);
    }
}
Y_UDONE()

