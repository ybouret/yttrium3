
//! \file

#ifndef Y_MPI_ScalerCarrier_Included
#define Y_MPI_ScalarCarrier_Included 1

#include "y/mpi++/carrier.hpp"

namespace Yttrium
{
    //! for arrays of scalar type
    class MPI::  ScalarCarrier : public Carrier
    {
    public:
        explicit ScalarCarrier(const MPI::DataType &) noexcept;
        virtual ~ScalarCarrier() noexcept;

        virtual void send(MPI &              mpi,
                          const void * const entry,
                          const size_t       items,
                          const size_t       target,
                          const int          tag);

        virtual void recv(MPI &         mpi,
                          void * const  entry,
                          const size_t  items,
                          const size_t  source,
                          const int     tag);

        const MPI::DataType &dataType;


    private:
        Y_Disable_Copy_And_Assign(ScalarCarrier);
    };

}


#endif // !Y_MPI_ScalerCarrier_Included
