
//! \file

#ifndef Y_MPI_VectorCarrier_Included
#define Y_MPI_VectorCarrier_Included 1

#include "y/mpi++/api.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Carrier for fixed-size vectors of scalar types
    //
    //
    //__________________________________________________________________________
    class MPI::  VectorCarrier : public Carrier
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit VectorCarrier(const MPI::DataType &,const size_t ) noexcept; //!< setup with type and dimensions
        virtual ~VectorCarrier() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
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

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        const MPI::DataType & scalarType; //!< base scalar type
        const size_t          dimensions; //!< vector dimensions



    private:
        Y_Disable_Copy_And_Assign(VectorCarrier); //!< discarded
    };

}

#endif // !Y_MPI_VectorCarrier_Included

