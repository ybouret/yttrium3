


//! \file

#ifndef Y_MKL_Half_Included
#define Y_MKL_Half_Included 1

#include "y/mkl/api/selector.hpp"
//#include <iostream>

namespace Yttrium
{
    namespace MKL
    {

        namespace Kernel
        {
            //! \param x value \return integer |x|
            template <typename T>
            inline T Half(const T x, const IntegralAPI &) noexcept
            {
                return x/2;
            }

            //! \param x value \return 0.5*x
            template <typename T>
            inline T Half(const T x, const FloatingAPI &) noexcept
            {
                static const T half = (T)(0.5);
                return x*half;
            }

            //! \param x value \return x.shr
            template <typename T>
            inline T  Half(const T &x, const MustCallAPI &) noexcept
            {
                T res(x);
                res.shr();
                return res;
            }

        }


        //! \param x value \return x/2
        template <typename T> inline
        T Half(typename TypeTraits<T>::ParamType x)
        {
            static const typename Kernel::Selected<T>::API choice = {};
            return Kernel::Half<T>(x,choice);
        }

        //! \param x value \param y value \return (x+y)/2
        template <typename T> inline
        T Half(typename TypeTraits<T>::ParamType x, typename TypeTraits<T>::ParamType y)
        {
            static const typename Kernel::Selected<T>::API choice = {};
            T sum = x+y;
            //T res = Kernel::Half<T>(sum,choice);
            //std::cerr << "x=" << x<< ", y=" << y << ", sum=" << sum << " => " << res << std::endl;
            return Kernel::Half<T>(sum,choice);
        }

        


    }

}

#endif // !Y_MKL_Half_Included

