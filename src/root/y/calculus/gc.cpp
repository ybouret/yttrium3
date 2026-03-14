#include "y/calculus/gc.hpp"
#include <cassert>

namespace Yttrium
{

    namespace Calculus
    {
        static inline
        uint64_t smallDivision(uint8_t w[], const uint8_t u[], const unsigned iv) noexcept
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

        uint64_t GC_:: Kept(const uint64_t qw, const uint8_t keep) noexcept
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
            assert(smallDivision(lhs,prod,keep) == qw);
            return smallDivision(lhs,prod,255);
        }
    }
}
