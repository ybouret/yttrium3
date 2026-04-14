#include "y/libc/file/buffer.hpp"
#include <cstdio>

namespace Yttrium
{
    namespace Libc
    {
        FileBuffer:: ~FileBuffer() noexcept
        {
        }

        FileBuffer:: FileBuffer() : FileBufferType(BUFSIZ)
        {
        }
    }
}
