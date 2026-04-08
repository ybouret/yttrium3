
#include "y/string/stride.hpp"
#include "y/memory/allocator/pooled.hpp"

namespace Yttrium
{

    namespace Core
    {


        Memory::Allocator &  Stride:: AllocatorInstance()
        {
            static Memory::Allocator &mgr = Memory::Pooled::Instance();
            return mgr;
        }

        Memory::Allocator &  Stride:: AllocatorLocation() noexcept
        {
            static Memory::Allocator &mgr = Memory::Pooled::Location();
            return mgr;
        }
    }

}


