//! \file

#ifndef Y_Concurrent_Nucleus_Included
#define Y_Concurrent_Nucleus_Included 1

#include "y/concurrent/singulet.hpp"

namespace Yttrium
{
    class Lockable;

    namespace Concurrent
    {

        class Nucleus : public Singulet
        {
        public:
            static const char * const CallSign; //!< "Nucleus"
            static const Longevity    LifeTime = GreatestLifeTime;
            class Code;

            virtual const char *  callSign() const noexcept;
            virtual Longevity     lifeTime() const noexcept;
            Lockable &            giant()          noexcept;
            
            static Nucleus & Instance();

        private:
            Y_Disable_Copy_And_Assign(Nucleus);
            explicit Nucleus();
            virtual ~Nucleus() noexcept;
            
            static void SelfDestruct(void * const) noexcept;

        };

    }
}

#endif // !Y_Concurrent_Nucleus_Included

