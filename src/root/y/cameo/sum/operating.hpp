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

            template <typename T, const bool>
            struct Genus;

            template <typename T>
            struct Genus<T,true>
            {
                typedef Scalar<T> Type;
            };

            template <typename T>
            struct Genus<T,false>
            {
                typedef Vectorial<typename T::Type,T> Type;
            };

            template <typename T>
            struct Operating
            {
                static const bool IsScalar = MKL::IsScalar<T>::Value;
                typedef typename Genus<T,IsScalar>::Type Type;
            };

        }

     


    }
}
#endif // !Y_Cameo_Sum_Operating_Included

