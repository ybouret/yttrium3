
//! \file

#ifndef Y_Calculus_RequiredBytes_Included
#define Y_Calculus_RequiredBytes_Included 1

#include "y/config/setup.hpp"
#include "y/type/ints.hpp"

namespace Yttrium
{
    namespace Calculus
    {
        //! compute bytes to hold given word
        struct RequiredBytes
        {
            static size_t For(const uint8_t  &) noexcept; //!< \return bytes to hold argument
            static size_t For(const uint16_t &) noexcept; //!< \return bytes to hold argument
            static size_t For(const uint32_t &) noexcept; //!< \return bytes to hold argument
            static size_t For(const uint64_t &) noexcept; //!< \return bytes to hold argument
        };
    }

    
    template <typename T> static inline
    size_t RequiredBytesFor(const T &x) noexcept
    {
        typedef typename UnsignedFor<sizeof(T)>::Alias::Type UType;
        return Calculus::RequiredBytes::For( (UType&)x );
    }

}

#endif // !Y_Calculus_RequiredBytes_Included

