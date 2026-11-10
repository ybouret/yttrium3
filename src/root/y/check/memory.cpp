#include "y/check/memory.hpp"

namespace Yttrium
{
    const void * CheckMemory:: GetUpper(const void * const entry,
                                        const size_t       bytes,
                                        const size_t       blockSize) noexcept
    {
        assert(entry);
        assert(bytes);
        assert(blockSize<=bytes);
        return (static_cast<const char *>(entry) + bytes)-blockSize;
    }

}
