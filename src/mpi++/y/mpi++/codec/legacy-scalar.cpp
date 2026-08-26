
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

}

