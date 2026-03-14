#include "y/memory/page.hpp"
#include <cassert>
#include <cstring>

namespace Yttrium
{
    namespace Memory
    {
        Page * Page:: From(void * const blockAddr) noexcept
        {
            assert(blockAddr);
            return static_cast<Page *>( memset(blockAddr,0,sizeof(Page)) );
        }
    }
}
