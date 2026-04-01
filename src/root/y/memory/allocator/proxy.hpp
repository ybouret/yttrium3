
//! \file

#ifndef Y_Memory_AllocatorProxy_Included
#define Y_Memory_AllocatorProxy_Included 1


#include "y/memory/allocator.hpp"

namespace Yttrium
{
    namespace Memory
    {
        template <typename ALLOCATOR>
        struct AllocatorProxy
        {
            static inline
            void * Acquire(size_t & blockSize)
            {
                static Memory::Allocator & mgr = ALLOCATOR::Instance();
                return mgr.acquire(blockSize);
            }

            static inline
            void Release(void * & blockAddr, size_t & blockSize) noexcept
            {
                static Memory::Allocator & mgr = ALLOCATOR::Location();
                mgr.release(blockAddr,blockSize);
            }
        };
    }

}

#endif // !Y_Memory_AllocatorProxy_Included
