
//! \file

#ifndef Y_Concurrent_Thread_Included
#define Y_Concurrent_Thread_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        class SystemThread;

        //______________________________________________________________________
        //
        //
        //
        //! Thread launching interface
        //
        //
        //______________________________________________________________________
        class Thread
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef void (*Proc)(void * const); //!< C-style function to launch

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! launch with persistent data
            /**
             - thread is built and launched
             \param threadProc procedure to call
             \param threadArgs PERISTENT arguments for threadProc
             */
            explicit Thread(Proc const threadProc, void * const threadArgs);

            //! wait for thread and cleanup
            virtual ~Thread() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! try to assign thread to cpu
            /**
             \param cpu cpu index
             \return true iff successfully assigned
             */
            bool assign(const size_t cpu) noexcept;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            Thread::Proc const        proc; //!< procedure
            void * const              args; //!< arguments (PERSISTENT)

        private:
            Y_Disable_Copy_And_Assign(Thread); //!< discarded
            SystemThread * const      impl;    //!< platform dependent
            Thread & self() noexcept;          //!< avoid this in constructor \return *this
        };
    }
}

#endif // !Y_Concurrent_Thread_Included

