#include "y/core/rand.hpp"
#include "y/libc/rand.h"
#include <ctime>

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

        Rand:: Rand() noexcept :
        seed( (long) time(NULL) )
        {
        }

        float Rand:: operator()() noexcept
        {
            return Yttrium_Randf(&seed);
        }
    }
}
