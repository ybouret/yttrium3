#include "y/mpi++/api.hpp"

namespace Yttrium
{

    namespace
    {
        static const char fn[] = "MPI_Bcast";
    }

    void MPI:: bcast(void * const       buffer,
                     const size_t       count,
                     const MPI_Datatype datatype,
                     const uint64_t     bytes,
                     const size_t       root)
    {
        Y_MPI_Mark();
        Y_MPI_Call(MPI_Bcast(buffer,
                             GetCount(count,fn),
                             datatype,
                             (int)root,
                             MPI_COMM_WORLD));
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


    void MPI:: bcastBytes(void * const buffer,
                          const size_t length,
                          const size_t root)
    {
        Y_MPI_Mark();
        Y_MPI_Call(MPI_Bcast(buffer,
                             GetCount(length,fn),
                             MPI_BYTE,
                             (int)root,
                             MPI_COMM_WORLD));
        const uint64_t ell = Y_MPI_Gain();
        if(root == rank)
        {
            sendRate.bytes += length;
            sendRate.ticks += ell;
        }
        else
        {
            recvRate.bytes += length;
            recvRate.ticks += ell;
        }
    }

}
