

//! \file

#ifndef Y_Cameo_FP_Queue_Included
#define Y_Cameo_FP_Queue_Included 1


#include "y/mkl/xreal.hpp"
#include "y/type/list.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        namespace Pith
        {
            typedef TL3(float,double,long double)                      StandardFloats; //!< \return alias
            typedef TL3(XReal<float>,XReal<double>,XReal<long double>) ExtendedFloats; //!< \return alias
        }

        //! compute parameters for given type
        template <typename T>
        struct UseFP_QueueAPI
        {
            static const bool Standard     = ( TL::IndexOf<Pith::StandardFloats,T>::Value >= 0 ); //!< alias
            static const bool Extended     = ( TL::IndexOf<Pith::ExtendedFloats,T>::Value >= 0 ); //!< alias
            static const bool IsApplicable = Standard || Extended;                                //!< alias
        };
    }

}


#endif // !Y_Cameo_FP_Queue_Included

