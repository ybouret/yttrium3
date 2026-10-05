//! \file

#ifndef Y_MPI_ScalarCarrier_Included
#define Y_MPI_ScalarCarrier_Included 1

#include "y/mpi++/carrier.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! for arrays of scalar type
    //
    //
    //__________________________________________________________________________
    class MPI::  ScalarCarrier : public Carrier
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit ScalarCarrier(const MPI::DataType &) noexcept; //!< setup
        virtual ~ScalarCarrier()                      noexcept; //!< cleanup

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
        const MPI::DataType &dataType; //!< persistent data type


    private:
        Y_Disable_Copy_And_Assign(ScalarCarrier); //!< discared
    };

}


#endif // !Y_MPI_ScalarCarrier_Included
