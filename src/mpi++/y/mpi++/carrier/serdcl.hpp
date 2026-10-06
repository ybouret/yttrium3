
//! \file

#ifndef Y_MPI_SerDclCarrier_Included
#define Y_MPI_SerDclCarrier_Included 1

#include "y/mpi++/api.hpp"
#include "y/stream/memory/output.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Base class for Serial Carriers
    //
    //
    //__________________________________________________________________________
    class MPI_Serial_Carrier : public MPI::Carrier
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char * const CallSign; //!< "MPI::SerialCarrier"

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit MPI_Serial_Carrier(const size_t) noexcept; //!< setup with min capacity
        virtual ~MPI_Serial_Carrier()             noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        OutputMemoryStream buffer; //!< I/O buffer

    protected:
        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! read buffer from source and tag \return loaded buffer
        const Memory::ReadOnlyBuffer & load(MPI &,const size_t,const int);

    private:
        Y_Disable_Copy_And_Assign(MPI_Serial_Carrier); //!< discarded
    };

}

#endif // !Y_MPI_SerDclCarrier_Included

