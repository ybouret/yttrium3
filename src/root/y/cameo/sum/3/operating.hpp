
//! \file

#ifndef Y_Cameo_Sum_OperationThree_Included
#define Y_Cameo_Sum_OperationThree_Included 1

#include "y/cameo/sum/3/scalar.hpp"
#include "y/cameo/sum/3/vectorial.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        namespace Sum {

            template <typename T, const bool> struct GenusThree;

            //! genus for scalar type
            template <typename T>
            struct GenusThree<T,true>
            {
                typedef ScalarThree<T> Type; //!< alias
            };

            //! genus for vectorial type
            template <typename T>
            struct GenusThree<T,false>
            {
                typedef VectorialThree<typename T::Type,T> Type; //!< aluas
            };

            //! select operating summator
            template <typename T>
            struct OperatingThree
            {
                static const bool IsScalar = MKL::IsScalar<T>::Value; //!< alias
                typedef typename GenusThree<T,IsScalar>::Type   Type; //!< alias
            };


        }

    }

}

#endif // !Y_Cameo_Sum_OperationThree_Included

