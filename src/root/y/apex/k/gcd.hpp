
//! \file

#ifndef Y_Apex_KegGCD_Included
#define Y_Apex_KegGCD_Included 1

#include "y/apex/k/cmp.hpp"
#include "y/apex/k/div.hpp"
#include "y/apex/k/dec.hpp"


namespace Yttrium
{
    namespace Apex
    {

        struct KegGCD
        {

            template <typename WORD, typename CORE> static inline
            Keg<WORD> * Compute(const WORD * const a,
                                const size_t       n,
                                const WORD * const b,
                                const size_t       m)
            {

                if(n<=0)
                {
                    //----------------------------------------------------------
                    //
                    // a = 0
                    //
                    //----------------------------------------------------------
                    if(m<=0)
                    {
                        //------------------------------------------------------
                        // b = 0
                        //------------------------------------------------------
                        return Keg<WORD>::One();  // return 1
                    }
                    else
                    {
                        assert(0!=b);
                        //------------------------------------------------------
                        // b > 0
                        //------------------------------------------------------
                        return new Keg<WORD>(b,m); // return b
                    }
                }
                else
                {
                    assert(0!=a);
                    //----------------------------------------------------------
                    //
                    // a > 0
                    //
                    //----------------------------------------------------------
                    if(m<=0)
                    {
                        //------------------------------------------------------
                        // b = 0
                        //------------------------------------------------------
                        return new Keg<WORD>(a,n);  // return a
                    }
                    else
                    {
                        assert(0!=b);
                        //------------------------------------------------------
                        // b > 0
                        //------------------------------------------------------
                        return Compute_<WORD,CORE>(a,n,b,m);
                    }

                }
            }

            template <typename WORD, typename CORE> static inline
            Keg<WORD> * Compute_(const WORD *   a,
                                 size_t         n,
                                 const WORD *   b,
                                 size_t         m)
            {
                typedef AutoPtr< Keg<WORD> > KegPtr;

                assert(0!=a);
                assert(n>0);  assert(a[n-1]!=0);
                assert(0!=b);
                assert(m>0);  assert(b[m-1]!=0);


                //--------------------------------------------------------------
                //
                // ensure a >= b
                //
                //--------------------------------------------------------------
                switch( KegCmp::Result(a,n,b,m) )
                {
                    case Negative:
                        Swap(a,b);
                        Swap(n,m);
                        break;

                    case __Zero__: // equality
                        return new Keg<WORD>(a,n);

                    case Positive:
                        break;
                }
                assert( KegCmp::Result(a,n,b,m) != Negative );

                //--------------------------------------------------------------
                //
                // Euclid's algorithm
                //
#if 0
                while(b>0)
                {
                    const T r = T(a%b);
                    a = b;
                    b = r;
                }

                return a;
#endif // 0
                //--------------------------------------------------------------

                // initialize
                KegPtr A = new Keg<WORD>(a,n);
                KegPtr B = new Keg<WORD>(b,m);

                std::cerr << "GCD(" << KegDec::ToString<WORD,CORE>(*A) << "," << KegDec::ToString<WORD,CORE>(*B) << ")" << std::endl;


                // iterative look up
                while(true)
                {
                    assert(A.isValid());
                    assert(B.isValid());
                    KegPtr R = KegDiv::Rem<WORD,CORE>(A->word,A->words,B->word,B->words); // R = A%B
                    //A = B;
                    //B = R;
                    //if(B->bits<=0) return A.yield();
                    return 0;
                }
            }



        };

    }
}

#endif // !Y_Apex_KegGCD_Included
