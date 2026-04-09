#include "y/calculus/required-bytes-for.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(calculus_required)
{
    Core::Rand ran;
    {
        uint8_t x = 0;
        Y_CHECK(0==Calculus::RequiredBytes::For(x));
        for(size_t i=1;i<=8;++i)
        {
            for(size_t iter=0;iter<10;++iter)
            {
                x = ran.gen<uint8_t>(i); Y_ASSERT(x>0);
                Y_ASSERT(1==Calculus::RequiredBytes::For(x));
            }
        }
    }

    
}
Y_UDONE()

