

//! \file

#ifndef Y_Cameo_Strategy_Included
#define Y_Cameo_Strategy_Included 1


#include "y/cameo/straight.hpp"
#include "y/cameo/ap-proxy.hpp"
#include "y/cameo/fp-queue.hpp"
#include "y/calculus/integer-log2.hpp"

namespace Yttrium
{
    namespace Cameo
    {

        enum Strategy
        {
            Straight = 0x00,
            AP_Proxy = 0x01,
            FP_Queue = 0x02
        };

        
        template <typename T>
        struct Selected
        {
            static const bool     _UseStraight = UseStraightAPI<T>::IsProper;
            static const bool     _UseAP_Proxy = UseAP_ProxyAPI<T>::IsProper;
            static const bool     _UseFP_Queue = UseFP_QueueAPI<T>::IsProper;
            static const unsigned ComputedUse =
            (_UseStraight ? 0x01 : 0) |
            (_UseAP_Proxy ? 0x02 : 0) |
            (_UseFP_Queue ? 0x04 : 0);
            static const unsigned UUID = IntegerLog2<ComputedUse>::Value;
        };
    }

}

#endif // !Y_Cameo_Strategy_Included

