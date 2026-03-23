
#include "y/memory/allocator/pooled.hpp"

namespace Yttrium
{
    namespace Memory
    {

        const char * const Pooled::CallSign = "Memory::Pooled";

        Pooled:: Pooled() : Singleton<Pooled,ClassLockPolicy>(), Allocator()
        {
        }

        Pooled:: ~Pooled() noexcept
        {
        }

    }

}

