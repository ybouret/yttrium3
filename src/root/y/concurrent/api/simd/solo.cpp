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

        size_t Solo:: size()     const noexcept { return 1; }
        size_t Solo:: capacity() const noexcept { return 1; }

        const Context & Solo:: ask(const size_t) const noexcept
        {
            return full;
        }



    }

}

