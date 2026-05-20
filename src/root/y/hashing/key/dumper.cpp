
#include "y/hashing/key/dumper.hpp"

namespace Yttrium
{

    namespace Hashing
    {

        template <> template<>
        uint16_t Dumping<uint16_t>::  From<uint8_t>(const uint8_t &x) noexcept
        {
            const uint16_t lo = x;
            const uint16_t hi = ~x;
            return lo | (hi<<8);
        }

    }

}
