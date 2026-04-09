#include "y/calculus/required-bytes.hpp"
#include "y/calculus/required-bits.hpp"

#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

namespace Yttrium
{
    static inline unsigned CountBitsFor(const uint8_t x) noexcept
    {
        unsigned  count = 8;
        uint8_t probe = 128;
        while(count>0)
        {
            if( 0 != (probe&x) ) return count;
            --count;
            probe >>= 1;
        }
        return count;
    }
}

#define CYCLES 1024

Y_UTEST(calculus_required)
{
    Core::Rand ran;

    if(true)
    {
        uint8_t x = 0;
        for(size_t i=0;i<16;++i)
        {
            std::cerr << "   ";
            for(size_t j=0;j<16;++j,++x)
            {
                std::cerr << ' ' << CountBitsFor(x);
                if(x<255) std::cerr << ',';
            }
            std::cerr << std::endl;
        }
    }

    std::cerr << "-- Testing 8 bits" << std::endl;
    {
        uint8_t x = 0;
        Y_CHECK(0==Calculus::RequiredBytes::For(x));
        Y_CHECK(0==Calculus::RequiredBits::For(x));

        for(size_t i=1;i<=8;++i)
        {
            for(size_t iter=0;iter<CYCLES;++iter)
            {
                x = ran.gen<uint8_t>(i); Y_ASSERT(x>0);
                Y_ASSERT(1==Calculus::RequiredBytes::For(x));
                Y_ASSERT(i==Calculus::RequiredBits::For(x));
            }
        }
    }
    std::cerr << std::endl;

    std::cerr << "-- Testing 16 bits" << std::endl;
    {
        uint16_t x = 0;
        Y_CHECK(0==Calculus::RequiredBytes::For(x));
        Y_CHECK(0==Calculus::RequiredBits::For(x));
        for(size_t i=1;i<=8;++i)
        {
            for(size_t iter=0;iter<CYCLES;++iter)
            {
                x = ran.gen<uint16_t>(i); Y_ASSERT(x>0);
                Y_ASSERT(1==Calculus::RequiredBytes::For(x));
                Y_ASSERT(i==Calculus::RequiredBits::For(x));
            }
        }

        for(size_t i=9;i<=16;++i)
        {
            for(size_t iter=0;iter<CYCLES;++iter)
            {
                x = ran.gen<uint16_t>(i); Y_ASSERT(x>0);
                Y_ASSERT(2==Calculus::RequiredBytes::For(x));
                Y_ASSERT(i==Calculus::RequiredBits::For(x));
            }
        }

    }
    std::cerr << std::endl;


    std::cerr << "-- Testing 32 bits" << std::endl;
    {
        uint32_t x = 0;
        Y_CHECK(0==Calculus::RequiredBytes::For(x));
        Y_CHECK(0==Calculus::RequiredBits::For(x));
        for(size_t i=1;i<=8;++i)
        {
            for(size_t iter=0;iter<CYCLES;++iter)
            {
                x = ran.gen<uint32_t>(i); Y_ASSERT(x>0);
                Y_ASSERT(1==Calculus::RequiredBytes::For(x));
                Y_ASSERT(i==Calculus::RequiredBits::For(x));
            }
        }

        for(size_t i=9;i<=16;++i)
        {
            for(size_t iter=0;iter<CYCLES;++iter)
            {
                x = ran.gen<uint32_t>(i); Y_ASSERT(x>0);
                Y_ASSERT(2==Calculus::RequiredBytes::For(x));
                Y_ASSERT(i==Calculus::RequiredBits::For(x));
            }
        }

        for(size_t i=17;i<=24;++i)
        {
            for(size_t iter=0;iter<CYCLES;++iter)
            {
                x = ran.gen<uint32_t>(i); Y_ASSERT(x>0);
                Y_ASSERT(3==Calculus::RequiredBytes::For(x));
                Y_ASSERT(i==Calculus::RequiredBits::For(x));
            }
        }

        for(size_t i=25;i<=32;++i)
        {
            for(size_t iter=0;iter<CYCLES;++iter)
            {
                x = ran.gen<uint32_t>(i); Y_ASSERT(x>0);
                Y_ASSERT(4==Calculus::RequiredBytes::For(x));
                Y_ASSERT(i==Calculus::RequiredBits::For(x));
            }
        }

    }
    std::cerr << std::endl;


    std::cerr << "-- Testing 64 bits" << std::endl;
    {
        uint64_t x = 0;
        Y_CHECK(0==Calculus::RequiredBytes::For(x));
        Y_CHECK(0==Calculus::RequiredBits::For(x));
        for(size_t i=1;i<=8;++i)
        {
            for(size_t iter=0;iter<CYCLES;++iter)
            {
                x = ran.gen<uint64_t>(i); Y_ASSERT(x>0);
                Y_ASSERT(1==Calculus::RequiredBytes::For(x));
                Y_ASSERT(i==Calculus::RequiredBits::For(x));
            }
        }

        for(size_t i=9;i<=16;++i)
        {
            for(size_t iter=0;iter<CYCLES;++iter)
            {
                x = ran.gen<uint64_t>(i); Y_ASSERT(x>0);
                Y_ASSERT(2==Calculus::RequiredBytes::For(x));
                Y_ASSERT(i==Calculus::RequiredBits::For(x));
            }
        }

        for(size_t i=17;i<=24;++i)
        {
            for(size_t iter=0;iter<CYCLES;++iter)
            {
                x = ran.gen<uint64_t>(i); Y_ASSERT(x>0);
                Y_ASSERT(3==Calculus::RequiredBytes::For(x));
                Y_ASSERT(i==Calculus::RequiredBits::For(x));
            }
        }

        for(size_t i=25;i<=32;++i)
        {
            for(size_t iter=0;iter<CYCLES;++iter)
            {
                x = ran.gen<uint64_t>(i); Y_ASSERT(x>0);
                Y_ASSERT(4==Calculus::RequiredBytes::For(x));
                Y_ASSERT(i==Calculus::RequiredBits::For(x));
            }
        }

        for(size_t i=33;i<=40;++i)
        {
            for(size_t iter=0;iter<CYCLES;++iter)
            {
                x = ran.gen<uint64_t>(i); Y_ASSERT(x>0);
                Y_ASSERT(5==Calculus::RequiredBytes::For(x));
                Y_ASSERT(i==Calculus::RequiredBits::For(x));
            }
        }

        for(size_t i=41;i<=48;++i)
        {
            for(size_t iter=0;iter<CYCLES;++iter)
            {
                x = ran.gen<uint64_t>(i); Y_ASSERT(x>0);
                Y_ASSERT(6==Calculus::RequiredBytes::For(x));
                Y_ASSERT(i==Calculus::RequiredBits::For(x));
            }
        }

        for(size_t i=49;i<=56;++i)
        {
            for(size_t iter=0;iter<CYCLES;++iter)
            {
                x = ran.gen<uint64_t>(i); Y_ASSERT(x>0);
                Y_ASSERT(7==Calculus::RequiredBytes::For(x));
                Y_ASSERT(i==Calculus::RequiredBits::For(x));
            }
        }

        for(size_t i=57;i<=64;++i)
        {
            for(size_t iter=0;iter<CYCLES;++iter)
            {
                x = ran.gen<uint64_t>(i); Y_ASSERT(x>0);
                Y_ASSERT(8==Calculus::RequiredBytes::For(x));
                Y_ASSERT(i==Calculus::RequiredBits::For(x));
            }
        }





    }
    std::cerr << std::endl;


}
Y_UDONE()

