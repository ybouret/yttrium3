

//! \file

#ifndef Y_Concurrent_FakeLock_Included
#define Y_Concurrent_FakeLock_Included 1

#include "y/ability/latch.hpp"
#include "y/ascii/base64/naming.hpp"

namespace Yttrium
{

    namespace Concurrent
    {
        //______________________________________________________________________
        //
        //
        //
        //! FakeLock, counting calls only
        //
        //
        //______________________________________________________________________
        class FakeLock : public Latch, public NamedAddress
        {
        public:
            static bool Verbose; //!< helper to trace calls
            
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit FakeLock() noexcept;
            virtual ~FakeLock() noexcept;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual bool tryLock() noexcept;
            virtual void lock()    noexcept;
            virtual void unlock()  noexcept;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t count; //!< lock count

        private:
            Y_Disable_Copy_And_Assign(FakeLock); //!< discarding
            void * self() noexcept;              //!< helper \return this
        };

    }

}

#endif // !Y_Concurrent_FakeLock_Included

