
#include "y/memory/allocator/pooled.hpp"
#include "y/memory/plastic/forge.hpp"
#include "y/concurrent/nucleus.hpp"
#include "y/type/destruct.hpp"

namespace Yttrium
{
    namespace Memory
    {

        const char * const Pooled::CallSign = "Memory::Pooled";

        namespace
        {
            static void *           PooledWorkspace[ Alignment::WordsFor<Plastic::Forge>::Count ];
            static Plastic::Forge * PooledForge = 0;
        }

        Pooled:: Pooled() : Singleton<Pooled,ClassLockPolicy>(), Allocator()
        {
            assert(0==PooledForge);
            try
            {
                PooledForge = new ( Y_BZero(PooledWorkspace) ) Plastic::Forge( Concurrent::Nucleus::Location().book, access);
            }
            catch(...)
            {
                Y_BZero(PooledWorkspace);
                PooledForge = 0;
                throw;
            }
        }

        Pooled:: ~Pooled() noexcept
        {
            assert(0!=PooledForge);
            Destruct(PooledForge);
            Y_BZero(PooledWorkspace) ;
            PooledForge = 0;
        }

        void * Pooled:: acquire(size_t &blockSize)
        {
            assert(0!=PooledForge);
            return PooledForge->acquire(blockSize);
        }

        void Pooled:: release(void * &blockAddr, size_t &blockSize) noexcept
        {
            assert(0!=PooledForge);
            PooledForge->release(blockAddr,blockSize);
        }


        void * Pooled:: legacyAcquire(const size_t blockSize)
        {
            assert(0!=PooledForge);
            return PooledForge->legacyAcquire(blockSize);
        }

        void Pooled:: legacyRelease(void * const blockAddr) noexcept
        {
            assert(0!=PooledForge);
            PooledForge->legacyRelease(blockAddr);
        }

    }

}

