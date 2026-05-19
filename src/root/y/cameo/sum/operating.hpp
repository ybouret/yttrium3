//! \file

#ifndef Y_Cameo_Sum_Operating_Included
#define Y_Cameo_Sum_Operating_Included 1


#include "y/cameo/sum/vectorial.hpp"
#include "y/mkl/api/scalar-for.hpp"

namespace Yttrium
{
    namespace Cameo
    {

        namespace Sum
        {

            template <typename T, const bool> struct Genus;

            //! genus for scalar type
            template <typename T>
            struct Genus<T,true>
            {
                typedef Scalar<T> Type; //!< alias
            };

            //! genus for vectorial type
            template <typename T>
            struct Genus<T,false>
            {
                typedef Vectorial<typename T::Type,T> Type; //!< aluas
            };

            //! select operating summator
            template <typename T>
            struct Operating
            {
                static const bool IsScalar = MKL::IsScalar<T>::Value; //!< alias
                typedef typename Genus<T,IsScalar>::Type        Type; //!< alias
            };

        }

     


    }
}
#endif // !Y_Cameo_Sum_Operating_Included

