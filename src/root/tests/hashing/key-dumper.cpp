#include "y/hashing/key/dumper.hpp"
#include "y/utest/run.hpp"

#include "y/hashing/ibj32.hpp"
#include "y/format/hexadecimal.hpp"

using namespace Yttrium;

Y_UTEST(hashing_key_dumper)
{
    uint32_t table[256];

    for(uint32_t i=0;i<256;++i)
    {
        const uint32_t h = Hashing::IBJ32(i);
        std::cerr << std::setw(3) << i << " => " << Hexadecimal(h) << std::endl;
        table[i] = h;
        for(uint32_t j=0;j<i;++j)
        {
            if( h == table[j] ) std::cerr << "collision!" << std::endl;
            
        }
    }
}
Y_UDONE()

