#include "y/memory/buffer/ro.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/check/crc32.hpp"

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

        uint32_t ReadOnlyBuffer:: crc() const noexcept
        {
            return CRC32:: Of( ro(), length() );
        }

    }
}


