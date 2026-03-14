#include "y/core/rand.hpp"
#include "y/libc/rand.h"
#include "y/check/crc32.hpp"
#include "y/system/pid.hpp"
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

        static inline
        long randSeed()
        {
            uint32_t crc = 0x00;
            {
                const time_t t = time(NULL);
                crc = CRC32::Run(t,crc);
            }
            {
                const uint64_t pid = System::ProcessID::Get();
                crc = CRC32::Run(pid,crc);
            }
            return (long)crc;
        }

        Rand:: Rand() noexcept :
        seed( randSeed() )
        {
        }

        float Rand:: operator()() noexcept
        {
            return Yttrium_Randf(&seed);
        }
    }
}
