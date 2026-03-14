
//! \file

#ifndef Y_Calculus_IAbs_Included
#define Y_Calculus_IAbs_Included 1

#include "y/type/ints.hpp"

namespace Yttrium
{

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
    namespace Calculus
    {

        template <typename T,bool> struct IAbs;

        template <typename T> struct IAbs<T,false>
        {
            static inline T Of(const T x) noexcept { return x; }
        };

        template <typename T> struct IAbs<T,true>
        {
            static inline T Of(const T x) noexcept { return x < 0 ? -x : x; }
        };

    }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

    //! integer absolute value \param x any integer type \return |x|
    template <typename T> inline
    T IAbs(const T x) noexcept
    {
        typedef Calculus::IAbs<T, IsSignedInt<T>::Value > API;
        return API::Of(x);
    }



}

#endif // !Y_Calculus_IAbs_Included
