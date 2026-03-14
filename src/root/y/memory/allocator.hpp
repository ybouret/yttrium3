//! \file

#ifndef Y_Memory_Allocator_Included
#define Y_Memory_Allocator_Included 1


#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {
        //! Memory Allocator interface
        class Allocator
        {
        protected:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Allocator() noexcept; //!< setup

        public:
            virtual ~Allocator() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // interface
            //
            //__________________________________________________________________

            //! acquire memory \param blockSize request, updated \return required memoy
            virtual void * acquire(size_t & blockSize)  = 0;

            //! release bytes \param blockAddr previously acquired block \param blockSize previously acquired bytes
            virtual void   release(void * & blockAddr, size_t &blockSize) noexcept = 0;

        private:
            Y_Disable_Copy_And_Assign(Allocator); //!< discarded
        };
    }
}

#endif // !Y_Memory_Allocator_Included

