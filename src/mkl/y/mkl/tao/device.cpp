
#include "y/mkl/tao/device.hpp"

namespace Yttrium
{
    namespace Tao
    {

        Device:: ~Device() noexcept
        {
        }

        Device:: Device(const Concurrent::Engine &engine) :
        Concurrent::Engine(engine)
        {
        }

        

    }
}
