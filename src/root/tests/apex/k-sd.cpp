#include "y/apex/k/div.hpp"
#include "y/apex/k/dec.hpp"

#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;
using namespace Apex;

namespace {

    template <typename WORD, typename CORE, size_t n>
    static inline void callKSD(Core::Rand &ran)
    {
        static const size_t      WordBits = sizeof(WORD) * 8;
        typedef Keg<WORD>        KegType;
        typedef AutoPtr<KegType> KegPtr;

        for(size_t iter=0;iter<10;++iter)
        {
            // numerator as array of words
            WORD          u[n];
            for(size_t i=0;i<n;++i)
                u[i] = ran.gen<WORD>(WordBits);
            const KegType numer(u,n);

            // denominator as single word
            const WORD    denom = ran.gen<WORD>( ran.in<size_t>(1,WordBits) );


            std::cerr << KegDec::ToString<WORD,CORE>(numer) << "=" << (uint64_t)denom << "*";


            WORD w[n]; Y_BZero(w);
            const WORD r = KegDiv::Small<WORD,CORE>(w, n, u, denom);
            KegType quot(WithAtLeast,n);
            Coerce(quot.words) = n;
            memcpy(quot.word,w,sizeof(w));
            quot.update();
            
            std::cerr << KegDec::ToString<WORD,CORE>(quot) << "+" << (uint64_t)r;

            const KegType D(CopyOf,denom);
            const KegType R(CopyOf,r);

            const KegPtr qd = KegMul::Compute<WORD,CORE>(quot.word,quot.words,D.word,D.words);
            const KegPtr nn = KegAdd::Compute<WORD,CORE>(qd->word,qd->words,R.word,R.words);

            std::cerr << "=" << KegDec::ToString<WORD,CORE>(*nn) << std::endl;

            Y_ASSERT(__Zero__== KegCmp::Result(numer.word, numer.words, nn->word, nn->words) );
        }

    }

    template <typename WORD, typename CORE>
    static inline void testKSD(Core::Rand &ran)
    {
        std::cerr << "-- small division <" << ( sizeof(WORD) * 8 ) << "," << ( sizeof(CORE) * 8 ) << ">" << std::endl;
        callKSD<WORD,CORE,1>(ran);
        callKSD<WORD,CORE,2>(ran);
        callKSD<WORD,CORE,3>(ran);
        callKSD<WORD,CORE,4>(ran);
        callKSD<WORD,CORE,5>(ran);
        callKSD<WORD,CORE,6>(ran);

        std::cerr << std::endl;
    }

}

Y_UTEST(apex_k_sd)
{
    Core::Rand ran;
    testKSD<uint8_t,uint16_t>(ran);
    testKSD<uint8_t,uint32_t>(ran);
    testKSD<uint8_t,uint64_t>(ran);
    testKSD<uint16_t,uint32_t>(ran);
    testKSD<uint16_t,uint64_t>(ran);
    testKSD<uint32_t,uint64_t>(ran);

}
Y_UDONE()

