
//! \file

#ifndef Y_Freezable_Included
#define Y_Freezable_Included 1

#include "y/config/setup.hpp"


namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Freezable interface
    //
    //
    //__________________________________________________________________________
    class Freezable
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit Freezable() noexcept; //!< setup
        virtual ~Freezable() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        void freeze() noexcept; //!< turn on frozen

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        const bool frozen; //!< status

    private:
        Y_Disable_Copy_And_Assign(Freezable); //!< discarded
    };

}

#endif // !Y_Freezable_Included
