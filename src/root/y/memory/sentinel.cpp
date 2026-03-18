#include "y/memory/sentinel.hpp"
#include "y/check/crc32.hpp"
#include "y/system/error.hpp"

#include <cerrno>
#include <cassert>

namespace Yttrium
{
    namespace Memory
    {
        Sentinel:: Sentinel(const char * const blockName,
                            const void * const blockAddr,
                            const size_t       blockSize) noexcept :
        name(blockName),
        addr(blockAddr),
        size(blockSize),
        crc( CRC32::Of(addr,size) )
        {
            assert(name);
        }

        Sentinel:: ~Sentinel() noexcept
        {
            const uint32_t end = CRC32::Of(addr,size);
            if(end!=crc)
                Libc::Error::Critical(EINVAL, "*** Memory::Sentinel on '%s'", name);
        }
    }
}
