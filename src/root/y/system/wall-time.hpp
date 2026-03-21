//! \file

#ifndef Y_System_WallTime_Included
#define Y_System_WallTime_Included 1


#include "y/memory/type/moniker.hpp"

namespace Yttrium
{
    namespace System
    {
        //______________________________________________________________________
        //
        //
        //
        //! Basic Wall-Time
        //
        //
        //______________________________________________________________________
        class WallTime
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit WallTime();          //!< setup
            virtual ~WallTime() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            static uint64_t Ticks();                               //!< unlocked ticks \return system ticks
            long double operator()(const uint64_t) const noexcept; //!< convert ticks \return seconds
            long double since(const uint64_t start) const;         //!< ellapsed time \param start origin \return seconds
            void        waitFor(const long double duration) const;
            
            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Memory::Moniker<long double> freq; //!< frequency with wraparound for MSC

        private:
            Y_Disable_Copy_And_Assign(WallTime); //!< discarded
            static long double Calibrate();      //!< calibrate clock \return frequency
        };
    }
}

//! update TICKS by ticks of CODE
#define Y_WallTime_Update(TICKS,CODE) \
/**/    do { \
/**/        const uint64_t __mark__ = Yttrium::System::WallTime::Ticks(); \
/**/        do { CODE; } while(false);                                    \
/**/        (TICKS) += Yttrium::System::WallTime::Ticks() - __mark__;     \
/**/    } while(false)

#endif // !Y_System_WallTime_Included

