//! \file

#ifndef Y_Memory_Sentinel_Included
#define Y_Memory_Sentinel_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {
        class Sentinel
        {
        public:
            Sentinel(const char * const blockName,
                     const void * const blockAddr,
                     const size_t       blockSize) noexcept;
            ~Sentinel() noexcept;


            const char * const name;
        private:
            Y_Disable_Copy_And_Assign(Sentinel);
            const void * const addr;
            const size_t       size;
            const uint32_t     crc;
        };
    }
}
#endif // !Y_Memory_Sentinel_Included

