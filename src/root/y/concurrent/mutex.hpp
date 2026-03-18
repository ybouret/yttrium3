
//! \file

#ifndef Y_Concurrent_Mutex_Included
#define Y_Concurrent_Mutex_Included 1

#include "y/ability/latch.hpp"

namespace Yttrium
{

    namespace Concurrent
    {
        class SystemMutex;

        //______________________________________________________________________
        //
        //
        //
        //! Portable Mutex
        //
        //
        //______________________________________________________________________
        class Mutex : public Latch
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Mutex();           //!< acquire system mutex
            virtual ~Mutex() noexcept;  //!< release system mutex

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void lock()    noexcept;
            virtual void unlock()  noexcept;
            virtual bool tryLock() noexcept;

            
        private:
            SystemMutex * const handle;       //!< system mutex handle
            Y_Disable_Copy_And_Assign(Mutex); //!< discarded
        };

    }

}

#endif // !Y_Concurrent_Mutex_Included
