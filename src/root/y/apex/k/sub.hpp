
//! \file

#ifndef Y_Apex_KegSub_Included
#define Y_Apex_KegSub_Included 1

#include "y/apex/k/keg.hpp"
#include "y/check/static.hpp"
#include "y/type/ints.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

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
            Keg<WORD> * Compute(const WORD * lhs,
                                const size_t nl,
                                const WORD * rhs,
                                const size_t nr)
            {
                Y_STATIC_CHECK(sizeof(WORD)<sizeof(CORE),BadSizes);
                typedef typename SignedFor<sizeof(CORE)>::Alias::Type CarryType;
                static const CarryType Radix     = CarryType(1) << (sizeof(WORD)*8);


                if(nl<=0)
                {
                    if(nr<=0)
                    {
                        return new Keg<WORD>();
                    }
                    else
                    {
                        assert(0!=rhs[nr-1]);
                        throw Libc::Exception(EDOM,"%s::Sub(Zero-Positive)", KegMetrics::CallSign);
                    }
                }
                else
                {
                    assert(0!=lhs[nl-1]);
                    if(nr<=0)
                    {
                        return new Keg<WORD>(lhs,nl);
                    }
                    else
                    {
                        assert(0!=rhs[nr-1]);
                        if(nr>nl)
                            Libc::Exception(EDOM,"%s::Sub(rhs>lhs) Level-1", KegMetrics::CallSign);
                        assert(nr<=nl);
                        Keg<WORD> * const res = new Keg<WORD>(WithAtLeast,nl);

                        //------------------------------------------------------
                        //
                        // common part
                        //
                        //------------------------------------------------------
#if defined(Y_Apex_Trace)
                        const uint64_t mark = System::WallTime::Ticks();
#endif
                        CarryType cr = 0;
                        WORD *    d = res->word;
                        for(size_t i=nr;i>0;--i)
                        {
                            cr += static_cast<CarryType>( *(lhs++) );
                            cr -= static_cast<CarryType>( *(rhs++) );
                            if(cr<0)
                            {
                                *(d++) = static_cast<WORD>(cr+Radix);
                                cr     = -1;
                            }
                            else
                            {
                                *(d++)  = static_cast<WORD>(cr);
                                cr      = 0;
                            }
                        }

                        //------------------------------------------------------
                        //
                        // propagate carry
                        //
                        //------------------------------------------------------
                        for(size_t i=nl-nr;i>0;--i)
                        {
                            cr += static_cast<CarryType>( *(lhs++) );
                            if(cr<0)
                            {
                                *(d++)  = static_cast<WORD>(cr+Radix);
                                cr      = -1;
                            }
                            else
                            {
                                *(d++)  = static_cast<WORD>(cr);
                                cr      = 0;
                            }
                        }

                        if(cr<0)
                            throw Libc::Exception(EDOM,"%s::Sub(rhs>lhs) Level-1", KegMetrics::CallSign);

                        Coerce(res->words) = nl;
                        res->update();
#if defined(Y_Apex_Trace)
                        Trace += System::WallTime::Ticks() - mark;
#endif
                        return res;
                    }
                }






            }

        };

    }

}


#endif // !Y_Apex_KegSub_Included

