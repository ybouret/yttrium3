#include "y/memory/buffer/ro.hpp"
#include "y/format/hexadecimal.hpp"

namespace Yttrium
{
    namespace Memory
    {
        ReadOnlyBuffer:: ReadOnlyBuffer() noexcept
        {
        }

        ReadOnlyBuffer:: ~ReadOnlyBuffer() noexcept
        {
        }

        std::ostream & operator<<(std::ostream &os, const ReadOnlyBuffer &buffer)
        {
            return Hexadecimal::Display(os, static_cast<const uint8_t *>(buffer.ro()), buffer.length());
        }

    }
}
