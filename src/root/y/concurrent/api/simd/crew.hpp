

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
            explicit Crew(const size_t n); //!< setup \param n number of threads
            virtual ~Crew() noexcept;      //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual size_t size()     const noexcept;
            virtual size_t capacity() const noexcept;
            
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

