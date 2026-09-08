//! \file

#ifndef Y_MKL_Scalar_Display_Included
#define Y_MKL_Scalar_Display_Included 1

#include "y/mkl/triplet.hpp"
#include "y/string.hpp"

namespace Yttrium
{
    namespace MKL
    {

        template <typename T> struct
        DisplayScalar
        {
            static inline
            std::ostream & On(std::ostream &os, const T &t)
            {
                return os << t;
            }
        };

        template <typename T>
        struct DisplayScalar< XReal<T> >
        {
            static inline
            std::ostream & On(std::ostream &os, const XReal<T> &t)
            {
                return os << t.str();
            }
        };
    }

}

#endif // !Y_MKL_Scalar_Display_Included

