
//! \file

#ifndef Y_MKL_Mod2_Included
#define Y_MKL_Mod2_Included 1

#include "y/mkl/api/scalar-for.hpp"
#include "y/mkl/api/selector.hpp"
#include <cmath>

namespace Yttrium
{

    namespace MKL
    {

        namespace Kernel
        {

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            struct Mod2
            {
                template <typename T> static inline
                T Of(const IntegralAPI &, const T x) noexcept { return x*x; }

                template <typename T> static inline
                T Of(const FloatingAPI &, const T x) noexcept { return x*x; }

                template <typename T> static inline
                typename ScalarFor<T>::Type Of(const MustCallAPI &, const T &x)
                {
                    return x.mod2();
                }
            };
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        }

        //! \param x any valid value \return |x|
        template <typename T> inline
        typename ScalarFor<T>::Type Mod2(typename TypeTraits<T>::ParamType x) {
            static const typename Kernel::Selected<T>::API api = {};
            return Kernel::Mod2::Of(api,x);
        }

    }

}

#endif // !Y_MKL_Mod2_Included
