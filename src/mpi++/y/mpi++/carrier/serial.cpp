
#include "y/mpi++/api.hpp"

namespace Yttrium
{
    const char * const MPI::SerialCarrier_::BufferName = "MPI::SerialCarrier";

    MPI::SerialCarrier_:: SerialCarrier_(const size_t minCapacity) :
    Carrier(),
    buffer(BufferName,minCapacity)
    {}

    MPI::SerialCarrier_:: ~SerialCarrier_() noexcept
    {
    }

    const Memory::ReadOnlyBuffer & MPI::SerialCarrier_:: load(MPI &mpi, const size_t source, const int tag)
    {
        const size_t blockSize = mpi.recvSize(source,tag);
        buffer->adjust(blockSize,0);
        mpi.recvBytes(buffer.rw(),blockSize,source,tag);
        return buffer;
    }
}
