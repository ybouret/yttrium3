#include "y/utest/memio.hpp"

namespace Yttrium
{
    namespace UTest
    {
        MemIO:: MemIO()  : mutex(), cond(), ready(0)
        {
        }

        MemIO:: ~MemIO() noexcept
        {

        }
    }
}
