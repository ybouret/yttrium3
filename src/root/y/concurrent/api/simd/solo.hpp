
//! \file

#ifndef Y_Concurrent_Solo_Included
#define Y_Concurrent_Solo_Included 1

#include "y/concurrent/api/simd.hpp"
#include "y/concurrent/fake-lock.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        //______________________________________________________________________
        //
        //
        //
        //! Sequential SIMD
        //
        //
        //______________________________________________________________________
        class Solo : public SIMD
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Solo() noexcept; //!< setup
            virtual ~Solo() noexcept; //!< cleanup


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
            
            Y_Disable_Copy_And_Assign(Solo); //!< discarded
            FakeLock sync;                   //!< sequential lock
            Context  full;                   //!< full range context

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

#endif // !Y_Concurrent_Solo_Included

