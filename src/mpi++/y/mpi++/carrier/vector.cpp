
#include "y/mpi++/carrier/vector.hpp"

namespace Yttrium
{

    MPI:: VectorCarrier:: VectorCarrier(const MPI::DataType &mdt,
                                        const size_t         dim) noexcept :
    scalarType(mdt),
    dimensions(dim)
    {
        assert(dimensions>0);
    }


    MPI:: VectorCarrier:: ~VectorCarrier() noexcept {}

    void MPI:: VectorCarrier:: send(MPI &              mpi,
                                    const void * const entry,
                                    const size_t       items,
                                    const size_t       target,
                                    const int          tag)
    {
        const size_t words = items * dimensions;
        mpi.send(entry,words,scalarType.value,scalarType.bytes*words,target,tag);
    }

    void MPI:: VectorCarrier:: recv(MPI &         mpi,
                                    void * const  entry,
                                    const size_t  items,
                                    const size_t  source,
                                    const int     tag)
    {
        const size_t words = items * dimensions;
        mpi.recv(entry,words,scalarType.value,scalarType.bytes*words,source,tag);
    }

    void MPI:: VectorCarrier:: sendrecv(MPI        &       mpi,
                                        const void * const sendEntry,
                                        const size_t       sendItems,
                                        const size_t       sendRank,
                                        void * const       recvEntry,
                                        const size_t       recvItems,
                                        const size_t       recvRank,
                                        const int          tag)
    {
        const size_t sendWords = sendItems * dimensions;
        const size_t recvWords = recvItems * dimensions;
        mpi.sendrecv(sendEntry,sendWords,scalarType.value,scalarType.bytes*sendWords,sendRank,
                     recvEntry,recvWords,scalarType.value,scalarType.bytes*recvWords,recvRank,
                     tag,tag);
    }

    MPI::Carrier * MPI:: CreateVectorCarrier(const DataType &mdt, const size_t dim)
    {
        return new VectorCarrier(mdt, dim);
    }

}
