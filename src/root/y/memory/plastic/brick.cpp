#include "y/memory/plastic/brick.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Memory
    {
        namespace Plastic
        {

            void Brick:: updateSize() noexcept
            {
                assert(0!=next);
                size = (static_cast<size_t>(next-this)-1) * sizeof(Brick);
            }
        }

    }

}
