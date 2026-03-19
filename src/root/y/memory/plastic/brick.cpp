#include "y/memory/plastic/brick.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Memory
    {
        namespace Plastic
        {

            size_t Brick:: BytesBetween(const Brick * const a,
                                        const Brick * const b) noexcept
            {
                return (static_cast<size_t>(b-a)-1) * sizeof(Brick);
            }

            void Brick:: updateSize() noexcept
            {
                assert(0!=next);
                size = BytesBetween(this,next);
                //size = (static_cast<size_t>(next-this)-1) * sizeof(Brick);
            }
        }

    }

}
