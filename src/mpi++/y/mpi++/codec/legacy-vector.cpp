

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

}

