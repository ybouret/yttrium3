
#include "y/apex/k/keg.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Apex;

namespace
{
    template <typename CORE> static inline
    void testBits()
    {

        std::cerr << "-- Testing bits for " << sizeof(CORE) * 8 << "-bits " << std::endl;
        for(size_t p=0;p<=50;++p)
        {
            Keg<CORE> k(TwoToThePowerOf,p);
            std::cerr << k << std::endl;
        }

        std::cerr << std::endl;
    }
}

Y_UTEST(apex_keg_bits)
{
    testBits<uint8_t>();
    testBits<uint16_t>();
    testBits<uint32_t>();

}
Y_UDONE()
