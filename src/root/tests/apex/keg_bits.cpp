
#include "y/apex/k/keg.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;
using namespace Apex;

namespace
{
    template <typename CORE> static inline
    void testBits(Core::Rand &ran)
    {

        std::cerr << "-- Testing bits for " << sizeof(CORE) * 8 << "-bits " << std::endl;
        for(size_t p=0;p<=50;++p)
        {
            Keg<CORE> k(TwoToThePowerOf,p);
            std::cerr << k << std::endl;
            while(k.bits)
            {
                k.shr();
                std::cerr << k << " / [" << k.toBin() << "]" << std::endl;
            }
            k.shr();
            std::cerr << k << " / [" << k.toBin() << "]" << std::endl;
        }

        {
            Keg<CORE> k(TwoToThePowerOf,40);
            std::cerr << k.toBin() << std::endl;
            while(k.bits)
            {
                k.shr( ran.in<size_t>(1,5) );
                std::cerr << k.toBin() << std::endl;
            }
        }


        std::cerr << std::endl;
    }
}

Y_UTEST(apex_keg_bits)
{
    Core::Rand ran;
    testBits<uint8_t> (ran);
    testBits<uint16_t>(ran);
    testBits<uint32_t>(ran);

    if(false)
        for(size_t i=0;i<32;++i)
        {
            uint32_t x = 1;
            x <<= i;
        printf("0x%x,\n",x);
        }

}
Y_UDONE()
