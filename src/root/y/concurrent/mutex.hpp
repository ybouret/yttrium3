
//! \file

#ifndef Y_Concurrent_Mutex_Included
#define Y_Concurrent_Mutex_Included 1

#include "y/ability/latch.hpp"

namespace Yttrium
{

    namespace Concurrent
    {
        class SystemMutex;

        class Mutex : public Latch
        {
        public:
            explicit Mutex();
            virtual ~Mutex() noexcept;

            virtual void lock()    noexcept;
            virtual void unlock()  noexcept;
            virtual bool tryLock() noexcept;

            SystemMutex * const handle;
        private:
            Y_Disable_Copy_And_Assign(Mutex);
        };

    }

}

#endif // !Y_Concurrent_Mutex_Included
