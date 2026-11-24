//! \file

#ifndef Y_Hide_Included
#define Y_Hide_Included 1

#include "y/config/compiler.h"

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

        //! \param addr anonymous address \return cast from address
        template <typename T> static inline
        T * Cast(void * const addr) noexcept {
            return static_cast<T*>( Address(addr) );
        }

        //! \param addr anonymous const address \return const cast from address
        template <typename T> static inline
        const T * Cast(const void * const addr) noexcept {
            return static_cast<const T*>( Address(addr) );
        }

        //! \param p object \return same but hidden object
        template <typename T> static inline
        T * Alias(T * const p) noexcept
        {
            return static_cast<T*>( Address(p) );
        }

        //! \param p object \return same but hidden object
        template <typename T> static inline
        const T * Alias(const T * const p) noexcept
        {
            return static_cast<const T*>( Address(p) );
        }

        
    };

}

#endif // !Y_Hide_Included
