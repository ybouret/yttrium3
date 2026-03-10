//! \file

#ifndef Y_Hide_Included
#define Y_Hide_Included 1


namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Hiding memory address to avoid aliasing
    //
    //
    //__________________________________________________________________________
    struct Hide
    {
        static void *       Address(void * const)       noexcept; //!< for mutable region  \return given address
        static const void * Address(const void * const) noexcept; //!< for constant region \return given address
    };

}

#endif // !Y_Hide_Included
