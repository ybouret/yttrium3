//! \file

#ifndef Y_GlobalMultiThreaded_Included
#define Y_GlobalMultiThreaded_Included 1

#include "y/threading/locker.hpp"
#include "y/threading/policy.hpp"

namespace Yttrium {

    class Lockable;

    //__________________________________________________________________________
    //
    //
    //
    //! use giant lock as authorization
    //
    //
    //__________________________________________________________________________
    class GlobalMultiThreaded : public Threading::Policy
    {
    public:
        typedef Threading::Locker<GlobalMultiThreaded> Lock; //!< alias

        explicit GlobalMultiThreaded();                            //!< setup
        virtual ~GlobalMultiThreaded()                   noexcept; //!< cleanup
        GlobalMultiThreaded(const GlobalMultiThreaded &) noexcept; //!< duplicate

        virtual void lock()   noexcept;
        virtual void unlock() noexcept;

    private:
        friend class Threading::Locker<GlobalMultiThreaded>;
        Y_Disable_Assign(GlobalMultiThreaded); //!< discarding
        Lockable * const authorization;        //!< & Lockable::Giant()
    };

}
#endif // !Y_GlobalMultiThreaded_Included

