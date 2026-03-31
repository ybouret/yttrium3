#include "y/concurrent/threaded.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        Casing * Casing:: data() noexcept { return this; }

        Casing::  ~Casing() noexcept {}

        Threaded:: ~Threaded() noexcept {}
    }
}
