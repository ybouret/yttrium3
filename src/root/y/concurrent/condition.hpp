
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


        //______________________________________________________________________
        //
        //
        //
        //! condition variable
        //
        //
        //______________________________________________________________________
        class Condition
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Condition();
            virtual ~Condition() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void wait(Mutex &) noexcept; //!< wait on a locked mutex
            void signal()      noexcept; //!< wake up one waiting thread
            void broadcast()   noexcept; //!< wake up all waiting threads

        private:
            SystemCondition * const handle;       //!< inner data
            Y_Disable_Copy_And_Assign(Condition); //!< discarded
        };
    }

}

#endif // !Y_Concurrent_Condition_Included
