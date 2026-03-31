#include "y/concurrent/threaded.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        ThreadingData * ThreadingData:: data() noexcept { return this; }

        ThreadingData::  ~ThreadingData() noexcept {}

        Threaded:: ~Threaded() noexcept {}
    }
}
