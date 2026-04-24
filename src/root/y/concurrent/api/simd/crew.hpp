

//! \file

#ifndef Y_Concurrent_Crew_Included
#define Y_Concurrent_Crew_Included 1

#include "y/concurrent/api/simd.hpp"

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
            class Code;
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Crew(const size_t n); //!< setup
            virtual ~Crew() noexcept; //!< cleanup

        private:
            Y_Disable_Copy_And_Assign(Crew); //!< discarded
            Code * const code;
            
            //__________________________________________________________________
            //
            //
            // interface
            //
            //__________________________________________________________________
            virtual void run();

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            SIMD & self() noexcept;
        };

    }

}

#endif // !Y_Concurrent_Crew_Included

