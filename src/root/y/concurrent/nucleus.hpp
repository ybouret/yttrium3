//! \file

#ifndef Y_Concurrent_Nucleus_Included
#define Y_Concurrent_Nucleus_Included 1

#include "y/concurrent/singulet.hpp"

namespace Yttrium
{
    class Lockable;

    namespace Concurrent
    {

        //______________________________________________________________________
        //
        //
        //
        //! Nucleus to store internal concurrency basics
        //
        //
        //______________________________________________________________________
        class Nucleus : public Singulet
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign;                    //!< "Nucleus"
            static const Longevity    LifeTime = GreatestLifeTime; //!< alias
            class Code;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const char *  callSign() const noexcept;
            virtual Longevity     lifeTime() const noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Lockable &       giant() noexcept; //!< access internal mutex \return lockable interface
            static Nucleus & Instance();       //!< handle instance \return single Nucleus

        private:
            Y_Disable_Copy_And_Assign(Nucleus); //!< discarded
            explicit Nucleus();                //!< setup internal code
            virtual ~Nucleus() noexcept;       //!< cleanup internal code

            //! call destructor at exit
            static void SelfDestruct(void * const) noexcept;

        };

    }
}

#endif // !Y_Concurrent_Nucleus_Included

