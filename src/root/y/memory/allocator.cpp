#include "y/memory/allocator.hpp"
#include "y/libc/str/len.h"
#include <cstring>

namespace Yttrium
{
    namespace Memory
    {
        Allocator:: ~Allocator() noexcept
        {
        }

        Allocator:: Allocator() noexcept
        {
        }


        char * Allocator:: createText(const char * const text, size_t &blockSize)
        {
            const size_t len = Yttrium_Strlen(text);
            void * const res = acquire(blockSize=len+1); assert(blockSize>len);
            return static_cast<char *>(memcpy(res,text,len));
        }

        void   Allocator:: deleteText(char * &blockAddr,  size_t &blockSize) noexcept
        {
            release( *(void **)&blockAddr, blockSize);
            assert(0==blockAddr);
            assert(0==blockSize);
        }
    }

}
