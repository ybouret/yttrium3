
#include "y/format/decimal.hpp"
#include "y/libc/block/zeroed.h"
#include <cerrno>

namespace Yttrium
{
    namespace Concurrent
    {

        void * Nucleus:: acquire(size_t & blockSize)
        {
            assert(blockSize<=MaxBlockSize);
            Y_Lock(code->mutex);
            blockSize = blockSize <= MinBlockSize ? MinBlockSize : Alignment::SystemMemory::Ceil(blockSize);
            void * const blockAddr = calloc(1,blockSize);
            if(!blockAddr)
            {
                const Decimal fmt(blockSize);
                blockSize = 0;
                throw Libc::Exception(ENOMEM,"Nucleus::acquire(%s)",fmt.c_str());
            }
            assert(Yttrium_Zeroed(blockAddr,blockSize));
            Code::RAM += blockSize;
            return blockAddr;

        }

        void Nucleus:: release(void * &blockAddr, size_t &blockSize) noexcept
        {
            assert(0!=blockAddr);
            assert(blockSize>=MinBlockSize);
            assert(blockSize<=MaxBlockSize);
            Y_Lock(code->mutex);
            free(blockAddr);
            Code::RAM -= blockSize;
            blockSize = 0;
            blockAddr = 0;
        }

    }

}
