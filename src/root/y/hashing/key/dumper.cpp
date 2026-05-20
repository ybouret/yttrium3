
#include "y/hashing/key/dumper.hpp"

namespace Yttrium
{

    namespace Hashing
    {

        template <> template<>
        uint16_t Dumping<uint16_t>::  From<uint8_t>(const uint8_t &x) noexcept
        {
            static const uint16_t u8max = 255;
            const uint16_t lo = x;
            const uint16_t hi = (uint16_t)(u8max-x);
            return (uint16_t)(lo | (hi<<8));
        }

    }

}
