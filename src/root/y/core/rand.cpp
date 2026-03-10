#include "y/core/rand.hpp"
#include "y/libc/rand.h"

namespace Yttrium
{
    namespace Core
    {
        Rand:: ~Rand() noexcept
        {
            seed = -1;
        }


        Rand:: Rand(const long init) noexcept :
        seed(init)
        {
        }

        float Rand:: operator()() noexcept
        {
            return Yttrium_Randf(&seed);
        }
    }
}
