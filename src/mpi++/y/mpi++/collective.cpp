#include "y/mpi++/api.hpp"

namespace Yttrium
{

    void MPI:: bcast(void * const       buffer,
                     const size_t       count,
                     const MPI_Datatype datatype,
                     const uint64_t     bytes,
                     const size_t       root,
                     const MPI_Comm     comm)
    {
        Y_MPI_Mark();
        Y_MPI_Call(MPI_Bcast(buffer,
                             GetCount(count,"MPI_Bcast"),
                             datatype,
                             (int)root,
                             comm));
        const uint64_t ell = Y_MPI_Gain();
        if(root == rank)
        {
            sendRate.bytes += bytes;
            sendRate.ticks += ell;
        }
        else
        {
            recvRate.bytes += bytes;
            recvRate.ticks += ell;
        }
    }


}
