#include "y/memory/allocator/global.hpp"

namespace Yttrium
{
    namespace Memory
    {

        const char * const Global::CallSign = "Memory::Global";

        Global:: Global() : Singleton<Global,Policy>(), Allocator()
        {
        }

        Global:: ~Global() noexcept
        {
        }

        void * Global:: acquire(size_t & blockSize)
        {
            static Concurrent::Nucleus & nucleus = Concurrent::Nucleus::Location();
            return nucleus.acquire(blockSize);
        }

        void Global:: release(void * &blockAddr, size_t &blockSize) noexcept
        {
            static Concurrent::Nucleus & nucleus = Concurrent::Nucleus::Location();
            nucleus.release(blockAddr,blockSize);
        }

    }

}


