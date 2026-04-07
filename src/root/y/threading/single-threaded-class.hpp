
//! \file

#ifndef Y_Single_Threaded_Class_Included
#define Y_Single_Threaded_Class_Included 1

#include "y/config/setup.hpp"
#include "y/threading/must-lock.hpp"
#include "y/threading/policy.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! no locking for Single-Threaded Classes
    //
    //
    //__________________________________________________________________________
    class SingleThreadedClass : public Threading::Policy
    {
    public:

        //! dummy lock
        class Lock
        {
        public:
            Lock(const SingleThreadedClass &) noexcept; //!< do nothing
            ~Lock() noexcept;                           //!< do nothing
        private:
            Y_Disable_Copy_And_Assign(Lock); //!< discarding
        };

        explicit SingleThreadedClass() noexcept; //!< setup
        virtual ~SingleThreadedClass() noexcept; //!< cleanup
        SingleThreadedClass(const SingleThreadedClass &) noexcept; //!< duplicate, do nothing

        virtual void lock()   noexcept;
        virtual void unlock() noexcept;

    private:
        Y_Disable_Assign(SingleThreadedClass); //!< discarding
    };
}

#endif // !Y_Single_Threaded_Class_Included

