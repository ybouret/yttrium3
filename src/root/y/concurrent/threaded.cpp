#include "y/concurrent/threaded.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        ThreadSkin * ThreadSkin:: data() noexcept { return this; }

        ThreadSkin::  ~ThreadSkin() noexcept {}

        Threaded:: ~Threaded() noexcept {}
    }
}
