#include "y/memory/sentinel.hpp"
#include "y/check/crc32.hpp"
#include "y/system/error.hpp"
#include "y/format/decimal.hpp"

#include <iostream>

#include <cerrno>
#include <cassert>

namespace Yttrium
{
    namespace Memory
    {

        uint32_t Sentinel:: chk() const noexcept
        {
            assert(0!=addr);
            assert(size>0);
            return CRC32::Of(addr,size);
        }

        Sentinel:: Sentinel(const void * const blockAddr,
                            const size_t       blockSize) noexcept :
        addr(blockAddr),
        size(blockSize),
        crc( chk() )
        {
        }

        bool Sentinel:: isUntouched() const noexcept
        {
            return chk() == crc;
        }

        bool Sentinel:: wasModified() const noexcept
        {
            return !isUntouched();
        }


        Sentinel:: ~Sentinel() noexcept
        {
            const uint32_t end = CRC32::Of(addr,size);
            if(end!=crc)
                Libc::Error::Critical(EINVAL, "*** Memory::Sentinel failure @%p[%s]", addr, Decimal(size).c_str() );
        }


    }
}
