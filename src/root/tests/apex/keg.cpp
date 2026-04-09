#include "y/apex/k/keg.hpp"
#include "y/utest/run.hpp"

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
        KegType k1(0);
        Y_PRINTV(k1.maxBytes);
        Y_PRINTV(k1.maxWords);

        k1.ld(0x1234);
        std::cerr << k1 << std::endl;


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

