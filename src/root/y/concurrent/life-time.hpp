
//! \file

#ifndef Y_Concurrent_LifeTime_Included
#define Y_Concurrent_LifeTime_Included 1

#include "y/concurrent/singulet.hpp"

namespace Yttrium
{


    //! helper to declare life time
#define Y_LifeTimeFor(CLASS) \
static const System::AtExit::Longevity CLASS = ConcurrentNucleus - (__LINE__-Helper)

    //__________________________________________________________________________
    //
    //
    //
    //! meta-computing life times
    //
    //
    //__________________________________________________________________________
    struct LifeTimeFor
    {
        static const System::AtExit::Longevity ConcurrentNucleus = Concurrent::Singulet::GreatestLifeTime; //!< top-level life-time
        static const System::AtExit::Longevity Helper = (__LINE__); //!< helper to deduce life times
        Y_LifeTimeFor(MemoryGlobal); //!< for Memory::Global
        Y_LifeTimeFor(MemoryPooled); //!< for Memory::Pooled
    };

}

#endif // !Y_Concurrent_LifeTime_Included

