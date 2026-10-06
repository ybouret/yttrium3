
#include "y/mpi++/carrier/serdcl.hpp"

namespace Yttrium
{
    const char * const MPI_Serial_Carrier::CallSign = "MPI::SerialCarrier";


    MPI_Serial_Carrier:: ~MPI_Serial_Carrier() noexcept
    {
    }

    MPI_Serial_Carrier:: MPI_Serial_Carrier(const size_t minCapacity) noexcept :
    Carrier(),
    buffer(CallSign,minCapacity)
    {}

    const Memory::ReadOnlyBuffer & MPI_Serial_Carrier:: load(MPI &mpi, const size_t source, const int tag)
    {
        const size_t blockSize = mpi.recvSize(source,tag);
        buffer->adjust(blockSize,0);
        mpi.recvBytes(buffer.rw(),blockSize,source,tag);
        return buffer;
    }


    const char * const MPI::SerialCarrier_::BufferName = "MPI::SerialCarrier";

    MPI::SerialCarrier_:: SerialCarrier_(const size_t minCapacity) :
    Carrier(),
    buffer(BufferName,minCapacity)
    {}

    MPI::SerialCarrier_:: ~SerialCarrier_() noexcept
    {
    }

}
