//! \file

#ifndef Y_Apex_KegDiv_Included
#define Y_Apex_KegDiv_Included 1

#include "y/apex/k/cmp.hpp"
#include "y/apex/k/mul.hpp"
#include "y/apex/k/sub.hpp"
#include "y/pointer/auto.hpp"
#include "y/system/exception.hpp"
#include <cerrno>


namespace Yttrium
{
    namespace Apex
    {

        //______________________________________________________________________
        //
        //
        //
        //! Division Algorithm
        //
        //
        //______________________________________________________________________
        struct KegDiv
        {

            //! divide with optional output
            /**
             \param quot  optional quotient pointer
             \param rem   optional remainder pointer
             \param numer numerator words
             \param nsize size of numerator
             \param denom denominator words
             \param dsize size of denominator
             */
            template <typename WORD,typename CORE> static inline
            void Compute(AutoPtr< Keg<WORD> > * quot,
                         AutoPtr< Keg<WORD> > * rem,
                         const WORD * const     numer,
                         const size_t           nsize,
                         const WORD * const     denom,
                         const size_t           dsize)
            {

                typedef Keg<WORD>        KegType;
                typedef AutoPtr<KegType> KegPtr;

                //--------------------------------------------------------------
                //
                //
                // checking initial cases
                //
                //
                //--------------------------------------------------------------
                switch( KegCmp::Result(numer,nsize,denom,dsize) )
                {
                    case Negative:
                        if(quot) *quot = KegType::Zero();
                        if(rem)  *rem  = new KegType(numer,nsize);
                        return;
                        
                    case __Zero__:
                        if(dsize<=0) throw Libc::Exception(EDOM,"%s undetermined 0/0", KegMetrics::CallSign);
                        if(quot) *quot = KegType::One();
                        if(rem)  *rem  = KegType::Zero();
                        return;

                    case Positive:
                        if(dsize<=0) throw Libc::Exception(EDOM,"%s division by 0",KegMetrics::CallSign);
                        break;
                }

                //--------------------------------------------------------------
                //
                //
                // Generic Algorithm numer>denom meaning numer >= 1 * denom...
                //
                //
                //--------------------------------------------------------------
                assert(nsize>=dsize);
                assert( Positive == KegCmp::Result(numer,nsize,denom,dsize) );

                //--------------------------------------------------------------
                //
                // ...hence starting from upper = 2
                //
                //--------------------------------------------------------------
                KegPtr       upper = KegType::Two();
                size_t       shift = 1;
                {
                    KegPtr probe = new KegType(denom,dsize);
                    probe = probe->shl(); // probe = denom * 2
                FIND_UPPER:
                    switch( KegCmp::Result(probe->word,probe->words,numer,nsize) )
                    {
                        case Negative: // upper * denom < numer
                            upper = upper->shl();
                            probe = probe->shl();
                            ++shift;
                            goto FIND_UPPER;

                        case __Zero__: // specific case upper * denom == numer
                            if( quot ) *quot = upper;
                            if( rem  ) *rem  = KegType::Zero();
                            return;

                        case Positive: // upper * denom > numer
                            break;
                    }
                }

                //--------------------------------------------------------------
                //
                // deducing lower
                //
                //--------------------------------------------------------------
                KegPtr lower = new KegType(TwoToThePowerOf,--shift);

#if !defined(NDEBUG)
                {
                    KegPtr probe = KegMul::Compute<WORD,CORE>(upper->word, upper->words, denom, dsize);
                    assert( Positive == KegCmp::Result(probe->word,probe->words,numer,nsize) );
                }
                
                {
                    KegPtr probe = KegMul::Compute<WORD,CORE>(lower->word, lower->words, denom, dsize);
                    assert( Negative == KegCmp::Result(probe->word,probe->words,numer,nsize) );
                }
#endif // !defined(NDEBUG)
                





            }

            template <typename WORD, typename CORE> static inline
            bool GT1(const AutoPtr< Keg<CORE> > &lhs,
                      const AutoPtr< Keg<CORE> > &rhs)
            {
                const AutoPtr< Keg<CORE> > dif = KegSub::Compute<WORD,CORE>(lhs->word,lhs->words,
                                                                            rhs->word,rhs->words);
                return dif->gt1();
            }

        };

    }

}

#endif // !Y_Apex_KegDiv_Included
