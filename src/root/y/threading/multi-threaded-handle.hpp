//! \file

#ifndef Y_MultiThreadedHandle_Included
#define Y_MultiThreadedHandle_Included 1

#include "y/threading/locker.hpp"
#include "y/threading/policy.hpp"

namespace Yttrium {

    class Lockable;
    
    //__________________________________________________________________________
    //
    //
    //
    //! Multit-Threaded class using another lockable
    //
    //
    //__________________________________________________________________________
    class MultiThreadedHandle : public Threading::Policy
    {
    public:
        typedef Threading::Locker<MultiThreadedHandle> Lock; //!< alias

        explicit MultiThreadedHandle(Lockable &handle)   noexcept; //!< setup \param handle PERSISTENT lockable
        virtual ~MultiThreadedHandle()                   noexcept; //!< cleanup
        MultiThreadedHandle(const MultiThreadedHandle &) noexcept; //!< duplicate

        virtual void lock()   noexcept;
        virtual void unlock() noexcept;
    private:
        friend class Threading::Locker<MultiThreadedHandle>;
        Y_Disable_Assign(MultiThreadedHandle); //!< discarding
        Lockable * const authorization;        //!< & handle
    };
    
}

#endif // !Y_MultiThreadedHandle_Included
