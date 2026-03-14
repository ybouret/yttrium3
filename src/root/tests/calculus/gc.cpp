#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/random/fill.hpp"
#include "y/format/hexadecimal.hpp"

namespace Yttrium
{
    namespace Calculus
    {
        struct GC
        {
            static uint64_t Keep(const uint64_t qw, const uint8_t keep) noexcept;
        };
    }
}

namespace Yttrium
{
    namespace Calculus
    {


        static inline
        uint64_t mpsdv(uint8_t w[], const uint8_t u[], const unsigned iv) noexcept
        {
            assert(iv>0);
            assert(iv<256);
            unsigned ir=0;
            for(int j=8;j>=0;--j) {
                const unsigned i=256*ir+u[j];
                w[j] = uint8_t (i/iv);
                ir   = i % iv;
            }
            uint64_t qw = w[0];
            for(unsigned i=1;i<8;++i)
            {
                qw |= uint64_t(w[i]) << (i<<3);
            }
            return qw;
        }



#define Y_GC_BYTE(i) uint8_t(qw>>(i*8))

        uint64_t GC:: Keep(const uint64_t qw, const uint8_t keep) noexcept
        {
            switch(keep)
            {
                case 0:   return 0;
                case 255: return qw;
                default:
                    break;
            }
            // make bytes
            uint8_t lhs[12] = {
                Y_GC_BYTE(0), Y_GC_BYTE(1),Y_GC_BYTE(2),Y_GC_BYTE(3),
                Y_GC_BYTE(4), Y_GC_BYTE(5),Y_GC_BYTE(6),Y_GC_BYTE(7),
                0,0,0,0
            };

            // compute product
            uint8_t prod[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
            {
                unsigned       carry    = 0;
                const unsigned k        = keep;
                for(size_t i=0;i<8;++i)
                {
                    carry  += unsigned(lhs[i]) * k;
                    prod[i] = uint8_t(carry);
                    carry >>= 8;
                }
                prod[8] = uint8_t(carry);
            }

            // divide
            assert(mpsdv(lhs,prod,keep) == qw);
            return mpsdv(lhs,prod,255);
        }
    }
}


using namespace Yttrium;



Y_UTEST(calculus_gc)
{

    Core::Rand ran;

    uint64_t qw = 0;
    for(size_t iter=0;iter<10;++iter)
    {
        Random::FillWord(ran,qw);
        std::cerr << Hexadecimal(qw) << std::endl;
        for(unsigned keep=0;keep<256;++keep)
        {
            const uint64_t kept = Calculus::GC::Keep(qw,keep);
            Y_ASSERT(kept<=qw);
        }
    }

    for(size_t size=0;size<=1000;size+=1+ran.leq<size_t>(10))
    {
        std::cerr << std::setw(5) << size;
        uint8_t keep = 0;
        while(true)
        {
            const size_t kept = Calculus::GC::Keep(size,keep);
            std::cerr << "|" << std::setw(4) << (int)keep << ":" << std::setw(5) << kept;
            if(255==keep) break;
        CHOOSE_DELTA:
            size_t delta = ran.leq<size_t>(255-keep);
            if(delta<=0) goto CHOOSE_DELTA;
            keep += delta;
        }
        std::cerr << std::endl;
    }




}
Y_UDONE()

