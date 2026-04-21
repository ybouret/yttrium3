
//! \file

#ifndef Y_Apex_KegMul_Included
#define Y_Apex_KegMul_Included 1

#include "y/apex/k/keg.hpp"
#include "y/check/static.hpp"


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
        //! Multiplication Algorithm
        //
        //
        //______________________________________________________________________
        struct KegMul
        {
        public:
            static uint64_t Trace; //!< optional tracing

            //! long multiplication algorithm
            /**
             \param a first array of words
             \param p length of a
             \param b second array of words
             \param q length of b
             \return product
             */
            template <typename WORD, typename CORE> static inline
            Keg<WORD> * Compute(const WORD * a,
                                const size_t p,
                                const WORD * b,
                                const size_t q)
            {
                static const size_t WordBits = sizeof(WORD) *8 ;
                if(p<=0||q<=0) return new Keg<WORD>();
                assert(a!=0);
                assert(b!=0);
                assert(p>0);
                assert(q>0);
                const size_t   n   = p+q;
                Keg<WORD> *    res = new Keg<WORD>(WithAtLeast,n);
#if defined(Y_Apex_Trace)
                const uint64_t mark = System::WallTime::Ticks();
#endif
                {
                    WORD * product = res->word;
                    for(size_t j=q;j>0;--j,++product)
                    {
                        const CORE B     = static_cast<CORE>(*(b++));
                        CORE       carry = 0;
                        for(size_t i=0;i<p;++i)
                        {
                            carry     += static_cast<CORE>(product[i]) + static_cast<CORE>(a[i]) * B;
                            product[i] = static_cast<WORD>(carry);
                            carry >>= WordBits;
                        }
                        product[p] =  static_cast<WORD>(carry);
                    }
                }
                Coerce(res->words) = n;
                res->update();
#if defined(Y_Apex_Trace)
                Trace += System::WallTime::Ticks() - mark;
#endif
                return res;
            }


            template <typename WORD, typename CORE> static inline
            Keg<WORD> * Square(const WORD * a,
                               const size_t p)
            {
                static const size_t WordBits = sizeof(WORD) *8 ;
                if(p<=0) return new Keg<WORD>();
                assert(a!=0);
                assert(p>0);
                const size_t   n   = p<<1;
                Keg<WORD> *    res = new Keg<WORD>(WithAtLeast,n);

                {
                    WORD * product = res->word;
                    const WORD * b = a;
                    for(size_t j=p;j>0;--j,++product)
                    {
                        const CORE B     = static_cast<CORE>(*(b++));
                        CORE       carry = 0;
                        for(size_t i=0;i<p;++i)
                        {
                            carry     += static_cast<CORE>(product[i]) + static_cast<CORE>(a[i]) * B;
                            product[i] = static_cast<WORD>(carry);
                            carry >>= WordBits;
                        }
                        product[p] =  static_cast<WORD>(carry);
                    }
                }
                Coerce(res->words) = n;
                res->update();
                return res;
            }

        };

    }
}

#endif // !Y_Apex_KegMul_Included

