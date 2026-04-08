//! \file

#ifndef Y_AutoLocking_Included
#define Y_AutoLocking_Included 1

#include "y/pointer/locking-proxy.hpp"



namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Auto locking mechanism for lockable objects
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class AutoLocking
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Expose(T,Type); //!< aliases
        typedef Smart::LockingProxy<Type>      ReturnType;      //!< alias
        typedef Smart::LockingProxy<ConstType> ConstReturnType; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param obj PERISTENT lockable object
        inline explicit AutoLocking( Type & obj ) noexcept : host( &obj ) { }

        //! cleanup
        inline virtual ~AutoLocking() noexcept {}

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        inline ReturnType      operator->()       noexcept { assert(host); return ReturnType(host);      } //!< \return locked proxy
        inline ConstReturnType operator->() const noexcept { assert(host); return ConstReturnType(host); } //!< \return locked proxy


    private:
        Y_Disable_Copy_And_Assign(AutoLocking); //!< discarded
        Type * const host;                      //!< PERSISTENT host
    };

}

#endif // !Y_AutoLocking_Included

