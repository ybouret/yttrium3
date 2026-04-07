//! \file

#ifndef Y_MultiThreadedObject_Included
#define Y_MultiThreadedObject_Included 1

#include "y/threading/locker.hpp"
#include "y/threading/policy.hpp"

namespace Yttrium {

    class Lockable;

    //__________________________________________________________________________
    //
    //
    //
    //! use a new Mutex as authorization
    //
    //
    //__________________________________________________________________________
    class MultiThreadedObject : public Threading::Policy
    {
    public:
        typedef Threading::Locker<MultiThreadedObject> Lock; //!< alias
        static const size_t WordsPerMutex = 2;

        explicit MultiThreadedObject();                   //!< setup
        virtual ~MultiThreadedObject() noexcept;          //!< cleanup
        MultiThreadedObject(const MultiThreadedObject &); //!< as setup

        virtual void lock()   noexcept;
        virtual void unlock() noexcept;

    private:
        friend class Threading::Locker<MultiThreadedObject>;
        Y_Disable_Assign(MultiThreadedObject); //!< discarding
        Lockable * const authorization;        //!< new Concurrent::Mutex
        void *           wksp[WordsPerMutex];  //!< put mutex here

        void setupInnerMutex();

    };

}

#endif // !Y_MultiThreadedObject_Included

