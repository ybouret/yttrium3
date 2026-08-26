
#include "y/mpi++/codec/legacy-scalar.hpp"

namespace Yttrium
{

    MPI:: LegacyScalarCodec:: ~LegacyScalarCodec() noexcept
    {

    }

    MPI:: LegacyScalarCodec:: LegacyScalarCodec(const MPI            & mpi,
                                                const std::type_info & tid) :
    Codec(tid),
    dataType( mpi.getDataType(tid) )
    {

    }

    void MPI:: LegacyScalarCodec::send(MPI &              mpi,
                                       const void * const blockAddr,
                                       const size_t       numBlocks,
                                       const size_t       dest,
                                       const int          tag)
    {
        mpi.send(blockAddr,numBlocks,dataType.dt,dataType.sz*numBlocks,dest,tag);
    }

}

