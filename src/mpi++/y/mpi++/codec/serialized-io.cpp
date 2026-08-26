

#include "y/mpi++/codec/serialized-io.hpp"

namespace Yttrium
{

    MPI:: SerializedIOCodec:: ~SerializedIOCodec() noexcept
    {

    }

    MPI:: SerializedIOCodec:: SerializedIOCodec(const std::type_info & tid) :
    Codec(tid),
    buffer( rtti.name() )
    {

    }

}

