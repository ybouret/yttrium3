
#include "y/format/decimal.hpp"
#include "y/libc/block/zeroed.h"
#include <cerrno>

namespace Yttrium
{
    namespace Concurrent
    {

        void * Nucleus:: acquire(size_t & blockSize)
        {
            Y_Lock(code->mutex);
            if(blockSize>0)
            {
                void * const blockAddr = calloc(1,blockSize);
                if(!blockAddr)
                {
                    const Decimal fmt(blockSize);
                    blockSize = 0;
                    throw Libc::Exception(ENOMEM,"Acquire(%s)",fmt.c_str());
                }
                assert(Yttrium_Zeroed(blockAddr,blockSize));
                Code::RAM += blockSize;
                return blockAddr;
            }
            else
            {
                return 0;
            }
        }

        void Nucleus:: release(void * &blockAddr, size_t &blockSize) noexcept
        {
            if(blockAddr)
            {
                Y_Lock(code->mutex);
                free(blockAddr);
                Code::RAM -= blockSize;
                blockSize = 0;
                blockAddr = 0;
            }
            else
            {
                assert(0==blockSize);
            }
        }

    }

}
