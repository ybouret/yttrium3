
#include "y/string/stride.hpp"
#include "y/memory/allocator/pooled.hpp"

namespace Yttrium
{

    namespace Core
    {


        Memory::Allocator &  StrideIO:: AllocatorInstance()
        {
            static Memory::Allocator &mgr = Memory::Pooled::Instance();
            return mgr;
        }

        Memory::Allocator &  StrideIO:: AllocatorLocation() noexcept
        {
            static Memory::Allocator &mgr = Memory::Pooled::Location();
            return mgr;
        }
    }

}


