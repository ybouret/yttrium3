
//! \file

#ifndef Y_MPI_SerDclCarrier_Included
#define Y_MPI_SerDclCarrier_Included 1

#include "y/mpi++/carrier.hpp"
#include "y/stream/memory/output.hpp"

namespace Yttrium
{
    class MPI_Serial_Carrier : public MPI::Carrier
    {
    public:
        static const char * const CallSign;

        explicit MPI_Serial_Carrier(const size_t minCapacity) noexcept;
        virtual ~MPI_Serial_Carrier() noexcept;

        OutputMemoryStream buffer;

    protected:
        const Memory::ReadOnlyBuffer & load(MPI &,const size_t,const int);

    private:
        Y_Disable_Copy_And_Assign(MPI_Serial_Carrier);
    };

}

#endif // !Y_MPI_SerDclCarrier_Included

