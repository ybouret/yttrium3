
#include "y/mpi++/codec/legacy-scalar.hpp"

namespace Yttrium
{

    MPI:: LegacyScalarCodec:: ~LegacyScalarCodec() noexcept
    {

    }

    MPI:: LegacyScalarCodec:: LegacyScalarCodec(const std::type_info &tid) :
    Codec(tid)
    {

    }

}

