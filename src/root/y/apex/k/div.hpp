//! \file

#ifndef Y_Apex_KegDiv_Included
#define Y_Apex_KegDiv_Included 1

#include "y/apex/k/cmp.hpp"
#include "y/pointer/auto.hpp"
#include "y/system/exception.hpp"
#include <cerrno>


namespace Yttrium
{
    namespace Apex
    {

        struct KegDiv
        {

            template <typename WORD> static inline
            void Compute(AutoPtr< Keg<WORD> > * quot,
                         AutoPtr< Keg<WORD> > * rem,
                         const WORD * const     numer,
                         const size_t           nsize,
                         const WORD * const     denom,
                         const size_t           dsize)
            {

                switch( KegCmp::Result(numer,nsize,denom,dsize) )
                {
                    case Negative:
                        if(quot) *quot = new Keg<WORD>();
                        if(rem)  *rem  = new Keg<WORD>(numer,nsize);
                        return;
                        
                    case __Zero__:
                        if(dsize<=0) throw Libc::Exception(EDOM,"%s undetermined 0/0", KegMetrics::CallSign);
                        if(quot) *quot = new Keg<WORD>(CopyOf,1);
                        if(rem)  *rem  = new Keg<WORD>();
                        return;

                    case Positive:
                        if(dsize<=0) throw Libc::Exception(EDOM,"%s division by 0",KegMetrics::CallSign);
                        break;
                }



            }
        };

    }

}

#endif // !Y_Apex_KegDiv_Included
