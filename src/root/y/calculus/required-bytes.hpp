
//! \file

#ifndef Y_Calculus_RequiredBytes_Included
#define Y_Calculus_RequiredBytes_Included 1

#include "y/config/setup.hpp"
#include "y/type/ints.hpp"

namespace Yttrium
{
    namespace Calculus
    {
        struct RequiredBytes
        {
            static size_t For(const uint8_t  &) noexcept;
            static size_t For(const uint16_t &) noexcept;
            static size_t For(const uint32_t &) noexcept;
            static size_t For(const uint64_t &) noexcept;
        };

    }

    template <typename T> static inline
    size_t RequiredBytesFor(const T &x) noexcept
    {
        typedef typename UnsignedFor<sizeof(T)>::Alias UType;
        return Calculus::RequiredBytes::For( (UType&)x );
    }

}

#endif // !Y_Calculus_RequiredBytes_Included

