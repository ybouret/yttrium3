
//! \file

#ifndef Y_Concurrent_Condition_Included
#define Y_Concurrent_Condition_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{

    namespace Concurrent
    {
        class SystemCondition;
        class Mutex;
        
        class Condition
        {
        public:
            explicit Condition();
            virtual ~Condition() noexcept;

            void wait(Mutex &) noexcept;
            void signal()      noexcept;
            void broadcast()   noexcept;

        private:
            SystemCondition * const handle;
            Y_Disable_Copy_And_Assign(Condition);
        };
    }

}

#endif // !Y_Concurrent_Condition_Included
