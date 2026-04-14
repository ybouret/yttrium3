//! \file

#ifndef Y_Memory_ReadOnlyBuffer_Included
#define Y_Memory_ReadOnlyBuffer_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {
        class ReadOnlyBuffer
        {
        public:
            explicit ReadOnlyBuffer() noexcept;
            virtual ~ReadOnlyBuffer() noexcept;

            virtual const void * ro()     const noexcept = 0;
            virtual size_t       length() const noexcept = 0;

        private:
            Y_Disable_Copy_And_Assign(ReadOnlyBuffer);
        };
    }

}
#endif // !Y_Memory_ReadOnlyBuffer_Included


