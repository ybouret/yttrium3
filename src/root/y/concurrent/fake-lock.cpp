#include "y/concurrent/fake-lock.hpp"
#include <cassert>
#include <iostream>

namespace Yttrium
{

    namespace Concurrent
    {

        bool FakeLock:: Verbose = false;

        FakeLock:: FakeLock() noexcept :
        NamedAddress( self() ),
        count(0)
        {
        }

        void * FakeLock:: self() noexcept
        {
            return this;
        }

        FakeLock:: ~FakeLock() noexcept
        {
            assert(0==count);
        }

        void FakeLock:: lock() noexcept
        {
            ++Coerce(count);
            if(Verbose) Y_Locked_Print(std::cerr, (*this) << ".lock   @" << count);
        }

        void FakeLock:: unlock()  noexcept
        {
            assert(count>0);
            --Coerce(count);
            if(Verbose) Y_Locked_Print(std::cerr, (*this) << ".unlock @" << count);
        }

        bool FakeLock:: tryLock() noexcept
        {
            ++Coerce(count);
            if(Verbose) Y_Locked_Print(std::cerr, (*this) << ".trylock@" << count);
            return true;
        }

        
    }

}
