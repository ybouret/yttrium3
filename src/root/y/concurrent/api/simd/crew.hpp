

//! \file

#ifndef Y_Concurrent_Crew_Included
#define Y_Concurrent_Crew_Included 1

#include "y/concurrent/api/simd.hpp"
#include "y/concurrent/thread/venue.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        //______________________________________________________________________
        //
        //
        //
        //! Paralle SIMD
        //
        //
        //______________________________________________________________________
        class Crew : public SIMD
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            class Code;
            static const char * const CallSign; //!< "InParallel"
            
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Crew(const Venue); //!< setup with threads venue
            virtual ~Crew() noexcept;   //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual size_t       size()     const noexcept;
            virtual size_t       capacity() const noexcept;
            virtual Lockable &   sync()           noexcept;
            virtual const char * callSign() const noexcept;

        private:
            virtual const Context & ask(const size_t) const noexcept;
            Y_Disable_Copy_And_Assign(Crew); //!< discarded
            Code * const code;               //!< inner code

            //__________________________________________________________________
            //
            //
            // interface
            //
            //__________________________________________________________________
            virtual void run();

            
        };

    }

}

#endif // !Y_Concurrent_Crew_Included

