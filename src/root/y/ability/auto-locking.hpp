//! \file

#ifndef Y_AutoLocking_Included
#define Y_AutoLocking_Included 1

#include "y/pointer/locking-proxy.hpp"



namespace Yttrium
{

    template <typename T>
    class AutoLocking
    {
    public:
        Y_Args_Expose(T,Type);
        typedef Smart::LockingProxy<Type>      ReturnType;      //!< alias
        typedef Smart::LockingProxy<ConstType> ConstReturnType; //!< alias

        inline explicit AutoLocking( Type & obj ) noexcept :
        host( &obj )
        {
        }

        inline virtual ~AutoLocking() noexcept {}

        inline ReturnType      operator->()       noexcept { assert(host); return ReturnType(host); }
        inline ConstReturnType operator->() const noexcept { assert(host); return ConstReturnType(host); }


    private:
        Y_Disable_Copy_And_Assign(AutoLocking);
        Type * const host;
    };

}

#endif // !Y_AutoLocking_Included

