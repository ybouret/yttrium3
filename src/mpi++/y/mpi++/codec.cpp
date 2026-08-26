
#include "y/mpi++/codec.hpp"

namespace Yttrium
{
    MPI:: Codec:: ~Codec() noexcept
    {
    }

    MPI:: Codec:: Codec(const std::type_info &tid) :
    rtti( RTTI::Of(tid) ),
    tkey( rtti )
    {
    }

    const AddrKey & MPI:: Codec:: key() const noexcept
    {
        return tkey;
    }


}
