#include "y/threading/global-multi-threaded.hpp"
#include "y/ability/lockable.hpp"

namespace Yttrium {

    GlobalMultiThreaded::  GlobalMultiThreaded() : authorization( & Lockable::Giant() ) {}

    GlobalMultiThreaded::  GlobalMultiThreaded(const GlobalMultiThreaded &_) noexcept :
    Threading::Policy(),
    authorization(_.authorization)
    {}

    GlobalMultiThreaded:: ~GlobalMultiThreaded() noexcept
    { Coerce(authorization) = 0; }


    void GlobalMultiThreaded:: lock() noexcept
    {
        assert(authorization);
        authorization->lock();
    }

    void GlobalMultiThreaded:: unlock() noexcept
    {
        assert(authorization);
        authorization->unlock();
    }

}
