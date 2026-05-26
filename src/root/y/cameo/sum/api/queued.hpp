
//! \file

#ifndef Y_Cameo_Sum_Queued_API
#define Y_Cameo_Sum_Queued_API 1


#include "y/mkl/xreal.hpp"
#include "y/check/static.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        namespace Sum
        {
            namespace Pith
            {
                typedef TL3(float,double,long double)                      StandardFloats; //!< \return alias
                typedef TL3(XReal<float>,XReal<double>,XReal<long double>) ExtendedFloats; //!< \return alias
            }

            //! compute parameters for given type
            template <typename T>
            struct ByQueuedAPI
            {
                static const bool Standard     = ( TL::IndexOf<Pith::StandardFloats,T>::Value >= 0 ); //!< alias
                static const bool Extended     = ( TL::IndexOf<Pith::ExtendedFloats,T>::Value >= 0 ); //!< alias
                static const bool IsProper     = Standard || Extended;                                //!< alias
            };

            //! helper for static check
#define Y_Cameo_Sum_Queued_Check() Y_STATIC_CHECK(ByQueuedAPI<MutableType>::IsProper,BadType)

        }
    }
}

#endif // !Y_Cameo_Sum_Queued_API
