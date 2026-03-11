#include "y/ability/lockable.hpp"

namespace Yttrium
{

    Lockable:: Lockable() noexcept
    {
    }

    Lockable:: ~Lockable() noexcept
    {
    }



    ScopedLock:: ScopedLock(Lockable &_) noexcept :
    host(_)
    {
        host.lock();
    }

    ScopedLock:: ~ScopedLock() noexcept
    {
        host.unlock();
    }


}
