#include "y/memory/auto-built.hpp"

namespace Yttrium
{
    namespace Memory
    {
        AutoBuiltArgs:: AutoBuiltArgs() noexcept : arg1(0), arg2(0), arg3(0), meth(0)
        {
        }

        AutoBuiltArgs:: ~AutoBuiltArgs() noexcept
        {
            
        }

        AutoBuiltArgs * AutoBuiltArgs:: args() noexcept { return this; }

    }


}
