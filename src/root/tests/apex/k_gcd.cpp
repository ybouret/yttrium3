
#include "y/apex/k/gcd.hpp"
#include "y/apex/k/dec.hpp"

#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/calculus/gcd.hpp"

using namespace Yttrium;
using namespace Apex;


namespace
{
    template <typename WORD, typename CORE>
    static inline
    void testGCD( Core::Rand & ran )
    {
        typedef Keg<WORD>        KegType;
        typedef AutoPtr<KegType> KegPtr;

        std::cerr << "-- GCD<" << sizeof(WORD)*8 << "," << sizeof(CORE) * 8 << ">" << std::endl;

        for(size_t i=0;i<=64;++i)
        {
            for(size_t j=0;j<=64;++j)
            {
                {
                    const natural_t lhs = ran.gen<natural_t>(i);
                    const natural_t rhs = ran.gen<natural_t>(j);
                    //const natural_t gcd = GreatestCommonDivisor(lhs,rhs);
                    const KegType   L(CopyOf,lhs);
                    const KegType   R(CopyOf,rhs);
                    KegPtr          G = KegGCD:: Compute<WORD,CORE>(L.word,L.words,R.word,R.words);
                }
            }
        }

    }

}

Y_UTEST(apex_k_gcd)
{

    Core::Rand ran;


    testGCD<uint8_t,uint16_t>(ran);
    testGCD<uint8_t,uint32_t>(ran);
    testGCD<uint8_t,uint64_t>(ran);

    testGCD<uint16_t,uint32_t>(ran);
    testGCD<uint16_t,uint64_t>(ran);

    testGCD<uint32_t,uint64_t>(ran);

}
Y_UDONE()

