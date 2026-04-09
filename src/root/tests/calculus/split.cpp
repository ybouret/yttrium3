#include "y/calculus/split-word.hpp"
#include "y/utest/run.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

#define CYCLES 128

Y_UTEST(calculus_split)
{
    Core::Rand ran;

    std::cerr << "-- Split To 8-Bits" << std::endl;
    {
        std::cerr << "\t-- from 16 bits" << std::endl;
        for(uint64_t i=0;i<65536;++i)
        {
            uint16_t        x = (uint16_t)i; //std::cerr << Hexadecimal(x) << std::endl;
            uint8_t * const p = Calculus::SplitWord::Make<uint8_t>::From(x);
            const uint64_t  w[2] = { p[0], p[1] };
            Y_ASSERT( (w[0] | (w[1] << 8)) == i );
        }

        std::cerr << "\t-- from 32 bits" << std::endl;
        for(size_t j=0;j<=32;++j)
        {
            for(size_t iter=0;iter<CYCLES;++iter)
            {
                const uint64_t  i = ran.gen<uint32_t>(j);
                uint32_t        x = (uint32_t) i;
                uint8_t * const p = Calculus::SplitWord::Make<uint8_t>::From(x);
                const uint64_t w[4] = { p[0], p[1], p[2], p[3] };
                Y_ASSERT( (w[0] | (w[1] << 8) | (w[2] << 16) | (w[3]<<24) ) == i );
            }
        }

        std::cerr << "\t-- from 64 bits" << std::endl;
        for(size_t j=0;j<=64;++j)
        {
            for(size_t iter=0;iter<CYCLES;++iter)
            {
                const uint64_t  i = ran.gen<uint64_t>(j);
                uint64_t        x = (uint64_t) i;
                uint8_t * const p = Calculus::SplitWord::Make<uint8_t>::From(x);
                const uint64_t  w[8] = { p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7] };
                Y_ASSERT( (w[0] | (w[1] << 8) | (w[2] << 16) | (w[3]<<24) | (w[4]<<32)  |  (w[5]<<40) |  (w[6]<<48) |  (w[7]<<56)  ) == i );
            }
        }
    }

    std::cerr << "-- Split To 16-Bits" << std::endl;
    {
        std::cerr << "\t-- from 32 bits" << std::endl;
        for(size_t j=0;j<=32;++j)
        {
            for(size_t iter=0;iter<CYCLES;++iter)
            {
                const uint64_t  i = ran.gen<uint32_t>(j);
                uint32_t        x = (uint32_t) i;
                uint16_t * const p = Calculus::SplitWord::Make<uint16_t>::From(x);
                const uint64_t w[4] = { p[0], p[1]  };
                Y_ASSERT( (w[0] | (w[1] << 16) ) == i );
            }
        }

        std::cerr << "\t-- from 64 bits" << std::endl;
        for(size_t j=0;j<=64;++j)
        {
            for(size_t iter=0;iter<CYCLES;++iter)
            {
                const uint64_t   i = ran.gen<uint64_t>(j);
                uint64_t         x = (uint64_t) i;
                uint16_t * const p = Calculus::SplitWord::Make<uint16_t>::From(x);
                const uint64_t   w[4] = { p[0], p[1], p[2], p[3] };
                Y_ASSERT( (w[0] | (w[1] << 16) | (w[2] << 32) | (w[3]<<48) ) == i );
            }
        }
    }

    std::cerr << "-- Split To 32-Bits" << std::endl;
    {
        std::cerr << "\t-- from 64 bits" << std::endl;
        for(size_t j=0;j<=64;++j)
        {
            for(size_t iter=0;iter<CYCLES;++iter)
            {
                const uint64_t   i = ran.gen<uint64_t>(j);
                uint64_t         x = (uint64_t) i;
                uint32_t * const p = Calculus::SplitWord::Make<uint32_t>::From(x);
                const uint64_t   w[2] = { p[0], p[1] };
                Y_ASSERT( (w[0] | (w[1] << 32) ) == i );
            }
        }
    }


    std::cerr << "-- I/O for 16 bits" << std::endl;
    for(size_t i=0;i<=16;++i)
    {
        for(size_t iter=0;iter<CYCLES;++iter)
        {
            const uint16_t origin = ran.gen<uint16_t>(i);
            uint16_t       gather=0;
            {
                uint8_t        b[2];
                Calculus::SplitWord::Expand(b,origin);
                Calculus::SplitWord::Gather(gather,b);
            }
            Y_ASSERT(origin==gather);
        }
    }

    std::cerr << "-- I/O for 32 bits" << std::endl;
    for(size_t i=0;i<=32;++i)
    {
        for(size_t iter=0;iter<CYCLES;++iter)
        {
            const uint32_t origin = ran.gen<uint32_t>(i);
            uint32_t       gather=0;
            {
                uint8_t        b[4];
                Calculus::SplitWord::Expand(b,origin);
                Calculus::SplitWord::Gather(gather,b);
            }
            Y_ASSERT(origin==gather);
            {
                uint16_t       w[2];
                gather = 0;
                Calculus::SplitWord::Expand(w,origin);
                Calculus::SplitWord::Gather(gather,w);
            }
            Y_ASSERT(origin==gather);
        }

    }

    std::cerr << "-- I/O for 64 bits" << std::endl;
    for(size_t i=0;i<=32;++i)
    {
        for(size_t iter=0;iter<CYCLES;++iter)
        {
            const uint64_t origin = ran.gen<uint64_t>(i);
            uint64_t       gather=0;
            {
                uint8_t        b[8];
                Calculus::SplitWord::Expand(b,origin);
                Calculus::SplitWord::Gather(gather,b);
            }
            Y_ASSERT(origin==gather);
            {
                gather = 0;
                uint16_t      w[4];
                Calculus::SplitWord::Expand(w,origin);
                Calculus::SplitWord::Gather(gather,w);
            }
            Y_ASSERT(origin==gather);
            {
                gather = 0;
                uint32_t d[2];
                Calculus::SplitWord::Expand(d,origin);
                Calculus::SplitWord::Gather(gather,d);
            }
            Y_ASSERT(origin==gather);
        }
    }


}
Y_UDONE()
