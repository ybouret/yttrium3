
//! \file

#ifndef Y_MPI_VectorCarrier_Included
#define Y_MPI_VectorCarrier_Included 1

#include "y/mpi++/carrier.hpp"

namespace Yttrium
{
    //! for arrays of vector type
    class MPI::  VectorCarrier : public Carrier
    {
    public:
        explicit VectorCarrier(const MPI::DataType &mdt,
                               const size_t         dim) noexcept;
        virtual ~VectorCarrier() noexcept;

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

        const MPI::DataType & scalarType;
        const size_t          dimensions;



    private:
        Y_Disable_Copy_And_Assign(VectorCarrier);
    };

}

#endif // !Y_MPI_VectorCarrier_Included

