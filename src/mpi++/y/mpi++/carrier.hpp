
//! \file

#ifndef Y_MPI_Carrier_Included
#define Y_MPI_Carrier_Included 1

#include "y/mpi++/api.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Carrier interface
    //
    //
    //__________________________________________________________________________
    class MPI::Carrier : public CountedObject
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef ArcPtr<Carrier>        Handle; //!< alias
        typedef HashMap<String,Handle> Table;  //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit Carrier() noexcept; //!< setup
        virtual ~Carrier() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________


        //! send array of objects
        /**
         \param mpi    instance
         \param entry  first object address
         \param items  number of objects
         \param target target rank
         \param tag    channel
         */
        virtual void send(MPI &              mpi,
                          const void * const entry,
                          const size_t       items,
                          const size_t       target,
                          const int          tag) = 0;

        //! receive array of objects
        /**
         \param mpi    instance
         \param entry  first object address
         \param items  number of objects
         \param source source rank
         \param tag    channel
         */
        virtual void recv(MPI &         mpi,
                          void * const  entry,
                          const size_t  items,
                          const size_t  source,
                          const int     tag) = 0;


    private:
        Y_Disable_Copy_And_Assign(Carrier); //!< discarded
    };
}

#endif // !Y_MPI_Carrier_Included

