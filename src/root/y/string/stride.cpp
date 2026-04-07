
#include "y/string/stride.hpp"
#include "y/memory/allocator/pooled.hpp"

namespace Yttrium
{

    CoreStride:: CoreStride() noexcept
    {
    }

    CoreStride:: ~CoreStride() noexcept
    {
    }

    Memory::Allocator & CoreStride:: AllocatorInstance()
    {
        static Memory::Allocator &mgr = Memory::Pooled::Instance();
        return mgr;
    }

    Memory::Allocator & CoreStride:: AllocatorLocation() noexcept
    {
        static Memory::Allocator &mgr = Memory::Pooled::Location();
        return mgr;
    }

}


