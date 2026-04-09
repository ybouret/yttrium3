
#include "y/calculus/required-bytes.hpp"

namespace Yttrium
{
    namespace Calculus
    {

        size_t RequiredBytes:: For(const uint8_t &x) noexcept
        {
            switch(x)
            {
                case 0: return 0;
                default:
                    break;
            }
            return 1;
        }

        size_t RequiredBytes:: For(const uint16_t &x) noexcept
        {
            static const uint16_t lim0 = 0x00;
            static const uint16_t lim1 = 0xff;
            if(x<=lim0) return 0;
            if(x<=lim1) return 1;
            return 2;
        }

        size_t RequiredBytes:: For(const uint32_t &x) noexcept
        {
            static const uint32_t lim0 = 0x00000000;
            static const uint32_t lim1 = 0x000000ff;
            static const uint32_t lim2 = 0x0000ffff;
            static const uint32_t lim3 = 0x00ffffff;
            if(x<=lim0) return 0;
            if(x<=lim1) return 1;
            if(x<=lim2) return 2;
            if(x<=lim3) return 3;
            return 4;
        }


        size_t RequiredBytes:: For(const uint64_t &x) noexcept
        {
            static const uint64_t lim0 = 0x00000000;
            static const uint64_t lim1 = 0x000000ff;
            static const uint64_t lim2 = 0x0000ffff;
            static const uint64_t lim3 = 0x00ffffff;
            static const uint64_t lim4 = 0xffffffff;
            static const uint64_t lim5 = (lim4<<8) | lim1;
            static const uint64_t lim6 = (lim5<<8) | lim1;
            static const uint64_t lim7 = (lim6<<8) | lim1;


            if(x<=lim0) return 0;
            if(x<=lim1) return 1;
            if(x<=lim2) return 2;
            if(x<=lim3) return 3;
            if(x<=lim4) return 4;
            if(x<=lim5) return 5;
            if(x<=lim6) return 6;
            if(x<=lim7) return 7;
            return 8;
        }




    }
}
