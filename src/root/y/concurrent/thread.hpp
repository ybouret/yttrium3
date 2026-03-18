
//! \file

#ifndef Y_Concurrent_Thread_Included
#define Y_Concurrent_Thread_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        class SystemThread;
        
        class Thread
        {
        public:
            typedef void (*Proc)(void * const);


            explicit Thread(Proc const threadProc, void * const threadArgs);
            virtual ~Thread() noexcept;

            Thread::Proc const        proc;
            void * const              args;
            
        private:
            Y_Disable_Copy_And_Assign(Thread);
            SystemThread * const      impl;
            Thread & self() noexcept;
        };
    }
}

#endif // !Y_Concurrent_Thread_Included

