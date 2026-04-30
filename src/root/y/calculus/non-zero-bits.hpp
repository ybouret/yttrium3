
//! \file

#ifndef Y_Calculus_NonZeroBits_Included
#define Y_Calculus_NonZeroBits_Included 1


#include "y/type/ints.hpp"

namespace Yttrium
{
    namespace Calculus
    {
        //! compute required bits to hold a given word
        struct NonZeroBits
        {
            static const size_t Table[256]; //!< precomputed 8-bits results
            static size_t For(const uint8_t  &) noexcept; //!< \return bits to hold word
            static size_t For(const uint16_t &) noexcept; //!< \return bits to hold word
            static size_t For(const uint32_t &) noexcept; //!< \return bits to hold word
            static size_t For(const uint64_t &) noexcept; //!< \return bits to hold word
        };

    }

    template <typename T> static inline
    size_t NonZeroBits(const T &x) noexcept
    {
        typedef typename UnsignedFor<sizeof(T)>::Alias::Type UType;
        return Calculus::NonZeroBits::For( (UType&)x );
    }
}

#endif // !Y_Calculus_NonZeroBits_Included

