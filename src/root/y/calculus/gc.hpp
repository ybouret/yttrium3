
//! \file

#ifndef Y_Calculus_GC_Included
#define Y_Calculus_GC_Included 1

#include "y/type/is-signed-int.hpp"
#include "y/config/compiler.h"

namespace Yttrium
{

    namespace Calculus
    {
        struct GC_
        {
            static uint64_t Kept(const uint64_t qw, const uint8_t keep) noexcept;
        };
        template <typename T,bool> struct GC;

        template <typename T>
        struct GC<T,false>
        {
            static inline T Kept(const T size, const uint8_t keep) noexcept
            {
                return (T) GC_::Kept(size,keep);
            }
        };

        template <typename T>
        struct GC<T,true>
        {
            static inline T Kept(const T size, const uint8_t keep) noexcept
            {
                return size < 0 ? -(T) GC_::Kept(-size,keep) : (T) GC_::Kept(size,keep);
            }
        };
    }

    struct GC
    {
        template <typename T> static inline
        T Kept(const T size, const uint8_t keep) noexcept
        {
            return Calculus::GC<T,IsSignedInt<T>::Value>::Kept(size,keep);
        }
    };

}

#endif // !Y_Calculus_GC_Included

