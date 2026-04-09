#include "y/apex/k/add.hpp"
#include "y/utest/run.hpp"
#include "y/pointer/auto.hpp"

using namespace Yttrium;
using namespace Apex;

namespace
{
    template <typename WORD, typename CORE> static inline
    void TestKeg()
    {
        typedef Keg<WORD> KegType;
        std::cerr << "-- Test Keg<" << KegType::WordBits << "> / " << sizeof(CORE)*8 << std::endl;
        Y_SIZEOF(KegType);
        Y_PRINTV(KegType::WordShift);
        const natural_t n1  = 0x1234;
        const natural_t n2  = 0x56789;
        const natural_t sum = n1+n2;
        KegType k1(0),k2(0);
        k1.ld(n1); std::cerr << "k1=" << k1 << std::endl;
        k2.ld(n2); std::cerr << "k2=" << k2 << std::endl;

        AutoPtr< Keg<WORD> > ksum = KegAdd:: Compute<WORD,CORE>(k1.word,k1.words,k2.word,k2.words);
        std::cerr << "sum=" << ksum << " / " << Hexadecimal(sum) << std::endl;

        std::cerr << std::endl;
    }

}

Y_UTEST(apex_keg)
{

    Y_PRINTV(KegMetrics::MaxBytes);
    std::cerr << std::endl;
    
    TestKeg<uint8_t,uint16_t>();
    TestKeg<uint8_t,uint32_t>();
    TestKeg<uint8_t,uint64_t>();
    TestKeg<uint16_t,uint32_t>();
    TestKeg<uint16_t,uint64_t>();
    TestKeg<uint32_t,uint64_t>();


}
Y_UDONE()

