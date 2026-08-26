

#include "y/mpi++/codec/legacy-vector.hpp"

namespace Yttrium
{

    MPI:: LegacyVectorCodec:: ~LegacyVectorCodec() noexcept
    {

    }

    MPI:: LegacyVectorCodec:: LegacyVectorCodec(const std::type_info &tid) :
    Codec(tid)
    {

    }

}

