//! \file

#ifndef Y_MPI_Codecs_Included
#define Y_MPI_Codecs_Included 1

#include "y/mpi++/codec/legacy-scalar.hpp"
#include "y/mpi++/codec/legacy-vector.hpp"
#include "y/mpi++/codec/serialized-io.hpp"

namespace Yttrium
{
    namespace MPI_Codec_Internal
    {
        template <typename T>
        struct IsVector
        {
            static const bool Value = false;
        };

        template <template <typename> class VEC, typename T>
        struct IsVector< VEC<T> >
        {
            static const bool Value = TypeTraits<T>::IsArithmetic;
        };
    }

    template <typename T> struct
    MPI_Codec_Select
    {
        static const bool IsSerializable = Y_Is_SuperSubClass_Strict(Serializable,T);
        static const bool IsLegacyScalar = !IsSerializable && TypeTraits<T>::IsArithmetic;
        static const bool IsLegacyVector = !IsSerializable && MPI_Codec_Internal::IsVector<T>::Value;
    };

}


#endif // !Y_MPI_Codecs_Included

