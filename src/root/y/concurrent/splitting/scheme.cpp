
#include "y/concurrent/splitting/scheme.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Splitting
        {

            Scheme:: Scheme(const size_t n) :
            parallelism(n),
            localMemory( new LocalCache() )
            {
                assert(parallelism>0);
            }

            Scheme:: Scheme(const Scheme &scheme) noexcept :
            parallelism(scheme.parallelism),
            localMemory(scheme.localMemory)
            {
            }

            Scheme:: ~Scheme() noexcept
            {
            }
            
        }

    }
}

