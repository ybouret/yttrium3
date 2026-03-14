//! \file

#ifndef Y_Memory_Allocator_Included
#define Y_Memory_Allocator_Included 1


#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {
        class Allocator
        {
        protected:
            explicit Allocator() noexcept;

        public:
            virtual ~Allocator() noexcept;

            virtual void * acquire(size_t & blockSize)  = 0;
            virtual void   release(void * & blockAddr, size_t &blockSize) noexcept = 0;

        private:
            Y_Disable_Copy_And_Assign(Allocator);
        };
    }
}

#endif // !Y_Memory_Allocator_Included

