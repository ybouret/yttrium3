

#include "y/config/platform.h"
#include "y/config/setup.hpp"

#if defined(Y_BSD)
#include <pthread.h>

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Nucleus
        {
            class Mutex
            {
            public:

                pthread_mutex_t mutex;
                
            private:
                Y_Disable_Copy_And_Assign(Mutex);
            };

        }

    }
}

#endif // defined(Y_BSD)
