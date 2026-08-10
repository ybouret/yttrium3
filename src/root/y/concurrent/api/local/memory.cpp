
#include "y/concurrent/api/local/memory.hpp"

namespace Yttrium
{
    namespace Concurrent
    {


        LocalMemory:: ~LocalMemory() noexcept
        {

        }

        LocalMemory:: LocalMemory(const LocalMemory &mem) noexcept :
        SharedLocalCache(mem)
        {
        }

        LocalMemory:: LocalMemory() :
        SharedLocalCache( new LocalCache() )
        {
        }
        
    }

}
