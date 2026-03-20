
#include "y/system/wall-time.hpp"

#include "y/system/exception.hpp"
#include "y/ability/lockable.hpp"

#if defined(Y_Darwin)
#include "wall-time/darwin.hxx"
#endif

#if defined(Y_WIN)
#include "wall-time/win.hxx"
#endif

#if defined(Y_Linux) || defined(Y_FreeBSD) || defined(Y_SunOS) || defined(Y_OpenBSD)
#include "wall-time/clock-gettime.hxx"
#endif


namespace Yttrium
{

    namespace System
    {
        WallTime:: WallTime() : freq( Calibrate() )
        {

        }

        WallTime:: ~WallTime() noexcept
        {
            
        }

        long double WallTime:: operator()(const uint64_t ticks) const noexcept
        {
            return *freq * static_cast<long double>(ticks);
        }

        long double WallTime:: since(const uint64_t start) const
        {
            return (*this)(Ticks()-start);
        }
    }

}
