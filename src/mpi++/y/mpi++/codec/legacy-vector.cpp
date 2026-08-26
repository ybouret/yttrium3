

#include "y/mpi++/codec/legacy-vector.hpp"

namespace Yttrium
{

    MPI:: LegacyVectorCodec:: ~LegacyVectorCodec() noexcept
    {

    }

    MPI:: LegacyVectorCodec:: LegacyVectorCodec(const MPI            & mpi,
                                                const std::type_info & tid,
                                                const size_t           dim) :
    Codec(tid),
    dataType( mpi.getDataType(tid) ),
    dimensions(dim)
    {
        
    }

    void MPI:: LegacyVectorCodec::send(MPI &              mpi,
                                       const void * const blockAddr,
                                       const size_t       numBlocks,
                                       const size_t       dest,
                                       const int          tag)
    {
        const size_t numScalars = numBlocks * dimensions;
        mpi.send(blockAddr,numScalars,dataType.dt,numScalars*dataType.sz,dest,tag);
    }

}

