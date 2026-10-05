
//! \file

#ifndef Y_MPI_Carrier_Included
#define Y_MPI_Carrier_Included 1

#include "y/mpi++/api.hpp"

namespace Yttrium
{
    class MPI::Carrier : public CountedObject
    {
    public:
        explicit Carrier() noexcept;
        virtual ~Carrier() noexcept;


        virtual void send(MPI &              mpi,
                          const void * const entry,
                          const size_t       items,
                          const size_t       target,
                          const int          tag) = 0;

        virtual void recv(MPI &         mpi,
                          void * const  entry,
                          const size_t  items,
                          const size_t  source,
                          const int     tag) = 0;


    private:
        Y_Disable_Copy_And_Assign(Carrier);
    };
}

#endif // !Y_MPI_Carrier_Included

