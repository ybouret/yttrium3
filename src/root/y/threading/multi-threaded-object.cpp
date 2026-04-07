#include "y/threading/multi-threaded-object.hpp"
#include "y/concurrent/mutex.hpp"
#include "y/type/destruct.hpp"
#include "y/libc/block/zero.h"
#include <new>

namespace Yttrium {

    MultiThreadedObject::  MultiThreadedObject() :
    authorization( 0 ),
    wksp()
    {
        setupInnerMutex();
    }

    void MultiThreadedObject:: setupInnerMutex()
    {
        Coerce(authorization) = new ( Y_BZero(wksp) ) Concurrent::Mutex();
    }

    MultiThreadedObject:: ~MultiThreadedObject() noexcept
    {
        Destruct(authorization);
        Coerce(authorization) = 0;
        Y_BZero(wksp);
    }

    MultiThreadedObject::  MultiThreadedObject(const MultiThreadedObject &) :
    authorization(0),
    wksp()
    {
        setupInnerMutex();
    }

}
