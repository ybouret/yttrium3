#include "y/concurrent/api/simd/solo.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        Solo:: Solo() noexcept : sync(), full(sync)
        {
        }

        Solo:: ~Solo() noexcept
        {
            
        }

        void Solo:: run()
        {
            assert(procedure);
            assert(arguments);
            procedure(full,*arguments);
        }
    }

}

