
#include "y/apex/k/bits.hpp"

namespace Yttrium
{
    namespace Apex
    {

        template <>
        const uint8_t BitsData<uint8_t>:: Mask[8] =
        {
            0x1,
            0x2,
            0x4,
            0x8,
            0x10,
            0x20,
            0x40,
            0x80
        };

        template <>
        const uint8_t BitsData<uint8_t>:: Not2[8] =
        {
            0xff - 0x1,
            0xff - 0x2,
            0xff - 0x4,
            0xff - 0x8,
            0xff - 0x10,
            0xff - 0x20,
            0xff - 0x40,
            0xff - 0x80
        };

        template <>
        const uint16_t BitsData<uint16_t>:: Mask[16] =
        {
            0x1,
            0x2,
            0x4,
            0x8,
            0x10,
            0x20,
            0x40,
            0x80,
            0x100,
            0x200,
            0x400,
            0x800,
            0x1000,
            0x2000,
            0x4000,
            0x8000
        };


        template <>
        const uint16_t BitsData<uint16_t>:: Not2[16] =
        {
            0xffff - 0x1,
            0xffff - 0x2,
            0xffff - 0x4,
            0xffff - 0x8,
            0xffff - 0x10,
            0xffff - 0x20,
            0xffff - 0x40,
            0xffff - 0x80,
            0xffff - 0x100,
            0xffff - 0x200,
            0xffff - 0x400,
            0xffff - 0x800,
            0xffff - 0x1000,
            0xffff - 0x2000,
            0xffff - 0x4000,
            0xffff - 0x8000
        };


        template <>
        const uint32_t BitsData<uint32_t>:: Mask[32] =
        {
            0x1,
            0x2,
            0x4,
            0x8,
            0x10,
            0x20,
            0x40,
            0x80,
            0x100,
            0x200,
            0x400,
            0x800,
            0x1000,
            0x2000,
            0x4000,
            0x8000,
            0x10000,
            0x20000,
            0x40000,
            0x80000,
            0x100000,
            0x200000,
            0x400000,
            0x800000,
            0x1000000,
            0x2000000,
            0x4000000,
            0x8000000,
            0x10000000,
            0x20000000,
            0x40000000,
            0x80000000
        };

        template <>
        const uint32_t BitsData<uint32_t>:: Not2[32] =
        {
           0xffffffff - 0x1,
           0xffffffff - 0x2,
           0xffffffff - 0x4,
           0xffffffff - 0x8,
           0xffffffff - 0x10,
           0xffffffff - 0x20,
           0xffffffff - 0x40,
           0xffffffff - 0x80,
           0xffffffff - 0x100,
           0xffffffff - 0x200,
           0xffffffff - 0x400,
           0xffffffff - 0x800,
           0xffffffff - 0x1000,
           0xffffffff - 0x2000,
           0xffffffff - 0x4000,
           0xffffffff - 0x8000,
           0xffffffff - 0x10000,
           0xffffffff - 0x20000,
           0xffffffff - 0x40000,
           0xffffffff - 0x80000,
           0xffffffff - 0x100000,
           0xffffffff - 0x200000,
           0xffffffff - 0x400000,
           0xffffffff - 0x800000,
           0xffffffff - 0x1000000,
           0xffffffff - 0x2000000,
           0xffffffff - 0x4000000,
           0xffffffff - 0x8000000,
           0xffffffff - 0x10000000,
           0xffffffff - 0x20000000,
           0xffffffff - 0x40000000,
           0xffffffff - 0x80000000
        };

    }
}
