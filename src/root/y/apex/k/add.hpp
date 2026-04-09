
//! \file

#ifndef Y_Apex_KegAdd_Included
#define Y_Apex_KegAdd_Included 1

#include "y/apex/k/keg.hpp"
#include "y/check/static.hpp"

namespace Yttrium
{
    namespace Apex
    {

        struct KegAdd
        {
        public:
            template <typename WORD, typename CORE> static inline
            Keg<WORD> * Compute(const WORD * const lhs,
                                const size_t       nlw,
                                const WORD * const rhs,
                                const size_t       nrw)
            {
                Y_STATIC_CHECK(sizeof(WORD)<sizeof(CORE),BadSizes);

                if(nlw<=0)
                {
                    if(nrw<=0)
                    {
                        return new Keg<WORD>(0);
                    }
                    else
                    {
                        return new Keg<WORD>(rhs,nrw);
                    }
                }
                else
                {
                    if(nrw<=0)
                    {
                        return new Keg<WORD>(lhs,nrw);
                    }
                    else
                    {
                        return (nlw<nrw) ? Perform<WORD,CORE>(lhs,nlw,rhs,nrw) : Perform<WORD,CORE>(rhs,nrw,lhs,nlw);
                    }
                }


            }

        private:
            template <typename WORD, typename CORE> static inline
            Keg<WORD> * Perform(const WORD * small,
                                const size_t smallSize,
                                const WORD * large,
                                const size_t largeSize)
            {
                assert(smallSize>0); assert(0!=small);
                assert(largeSize>0); assert(0!=large);
                assert(smallSize<=largeSize);
                const size_t      WordBits = 8*sizeof(WORD);
                const size_t      numWords    = largeSize + 1;
                Keg<WORD> * const keg         = new Keg<WORD>(WithAtLeast,numWords);

                {
                    CORE   carry = 0;
                    WORD * sum   = keg->word;
                    for(size_t i=smallSize;i>0;--i)
                    {
                        carry   += static_cast<CORE>(*(small++));
                        carry   += static_cast<CORE>(*(large++));
                        *(sum++) = static_cast<WORD>(carry);
                        carry >>= WordBits;
                    }

                    for(size_t i=largeSize-smallSize;i>0;--i)
                    {
                        carry   += static_cast<CORE>(*(large++));
                        *(sum++) = static_cast<WORD>(carry);
                        carry >>= WordBits;
                    }
                    
                    *sum = static_cast<WORD>(carry);

                }

                Coerce(keg->words) = numWords;
                keg->update();
                return keg;
            }
        };




    }

}

#endif // !Y_Apex_KegAdd_Included

