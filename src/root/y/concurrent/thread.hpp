
//! \file

#ifndef Y_Concurrent_Thread_Included
#define Y_Concurrent_Thread_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        class Thread
        {
        public:
            typedef void (*Proc)(void * const);


            virtual ~Thread() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Thread);
        };
    }
}

#endif // !Y_Concurrent_Thread_Included

