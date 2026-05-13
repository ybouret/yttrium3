
//! \file

#ifndef Y_MKL_Sqrt_Included
#define Y_MKL_Sqrt_Included 1

#include "y/mkl/api/selector.hpp"
#include "y/calculus/isqrt.hpp"
#include <cmath>

namespace Yttrium
{

    namespace MKL
    {

        namespace Kernel
        {
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            struct Sqrt
            {
                template <typename T> static inline
                T Of(const IntegralAPI &, const T x) noexcept { return IntegerSquareRoot(x); }

                template <typename T> static inline
                T Of(const FloatingAPI &, const T x) noexcept { return std::sqrt(x); }

                template <typename T> static inline
                T Of(const MustCallAPI &, const T &x) { return x.sqrt(); }

            };
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
        }

        //! \param x any valid value \return x^(1/2)
        template <typename T> inline
        T Sqrt(typename TypeTraits<T>::ParamType x) {
            static const typename Kernel::Selected<T>::API api = {};
            return Kernel::Sqrt::Of(api,x);
        }

    }

}

#endif // !Y_MKL_Sqrt_Included
