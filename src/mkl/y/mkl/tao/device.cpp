
#include "y/mkl/tao/device.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace MKL
    {

        namespace Tao
        {




            Device:: ~Device() noexcept
            {

            }

            Device:: Device(const Concurrent::Engine &engine) :
            Concurrent::Engine(engine),
            scheme(simd->size()),
            tiles1d(scheme,simd->sync()),
            tiles2d(scheme,simd->sync()),
            udts(scheme,simd->sync())
            {
            }
            

            Tiles1D & Device:: remap1d(const size_t n) noexcept
            {
                tiles1d.remap(1,n, simd->sync());
                return tiles1d;
            }

        }


    }
}
