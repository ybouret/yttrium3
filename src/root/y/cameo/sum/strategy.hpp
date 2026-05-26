
//! \file

#ifndef Y_Cameo_Scalar_Sum_Strategy_Included
#define Y_Cameo_Scalar_Sum_Strategy_Included 1


#include "y/cameo/sum/api/direct.hpp"
#include "y/cameo/sum/api/raised.hpp"
#include "y/cameo/sum/api/queued.hpp"
#include "y/calculus/integer-log2.hpp"

namespace Yttrium
{
    namespace Cameo
    {

        namespace Sum
        {

            //__________________________________________________________________
            //
            //
            //
            //! Find out compute strategy
            //
            //
            //__________________________________________________________________
            template <typename T>
            struct Strategy
            {
                Y_Args_Expose(T,Type); //!< aliases
                static const unsigned UseDirect = ByDirectAPI<MutableType>::IsProper ? 0x01 : 0x00; //!< flag
                static const unsigned UseRaised = ByRaisedAPI<MutableType>::IsProper ? 0x02 : 0x00; //!< flag
                static const unsigned UseQueued = ByQueuedAPI<MutableType>::IsProper ? 0x04 : 0x00; //!< flag
                static const unsigned UseResult = UseDirect | UseRaised | UseQueued;                //!< selection flag
                static const unsigned Index     = IntegerLog2<UseResult>::Value;                    //!< selection index
            };

        }

    }

}

#endif // !Y_Cameo_Scalar_Sum_Strategy_Included
