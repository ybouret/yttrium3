
#include "y/threading/single-threaded-class.hpp"

namespace Yttrium
{
    SingleThreadedClass::  SingleThreadedClass() noexcept {}
    SingleThreadedClass:: ~SingleThreadedClass() noexcept {}
    SingleThreadedClass::  SingleThreadedClass( const SingleThreadedClass &) noexcept :
    Threading::Policy()
    {}


    SingleThreadedClass:: Lock:: Lock(const SingleThreadedClass&) noexcept
    {
    }

    SingleThreadedClass:: Lock:: ~Lock() noexcept
    {
    }


    void SingleThreadedClass:: lock()   noexcept {}
    void SingleThreadedClass:: unlock() noexcept {}


}
