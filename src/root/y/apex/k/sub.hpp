
//! \file

#ifndef Y_Apex_KegSub_Included
#define Y_Apex_KegSub_Included 1

#include "y/apex/k/keg.hpp"
#include "y/check/static.hpp"
#include "y/type/ints.hpp"

#if defined(Y_Apex_Trace)
#include "y/system/wall-time.hpp"
#endif

namespace Yttrium
{
    namespace Apex
    {

        //______________________________________________________________________
        //
        //
        //
        //! Subtraction Algorithm
        //
        //
        //______________________________________________________________________
        struct KegSub
        {
        public:
            static uint64_t Trace; //!< optional tracing

            //! compute sum
            /**
             \param lhs lhs words
             \param nlw lhs size
             \param rhs rhs words
             \param nrw rhs size
             \return sum
             */
            template <typename WORD, typename CORE> static inline
            Keg<WORD> * Compute(const WORD * const lhs,
                                const size_t       nl,
                                const WORD * const rhs,
                                const size_t       nr)
            {
                Y_STATIC_CHECK(sizeof(WORD)<sizeof(CORE),BadSizes);
                typedef typename SignedFor<sizeof(CORE)>::Alias::Type CarryType;

                

            }

        };

    }

}


#endif // !Y_Apex_KegSub_Included

