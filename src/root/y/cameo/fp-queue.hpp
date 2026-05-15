

//! \file

#ifndef Y_Cameo_FP_Queue_Included
#define Y_Cameo_FP_Queue_Included 1


#include "y/mkl/xreal.hpp"
#include "y/type/list.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        struct Pith
        {
            typedef TL3(float,double,long double)                      StandardFloats;
            typedef TL3(XReal<float>,XReal<double>,XReal<long double>) ExtendedFloats;
        };

        template <typename T>
        struct UseFP_QueueAPI
        {
            static const bool Standard = ( TL::IndexOf<Pith::StandardFloats,T>::Value >= 0 );
            static const bool Extended = ( TL::IndexOf<Pith::ExtendedFloats,T>::Value >= 0 );
            static const bool IsApplicable = Standard || Extended;
        };
    }

}


#endif // !Y_Cameo_FP_Queue_Included

