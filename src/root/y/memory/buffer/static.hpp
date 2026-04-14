
//! \file

#ifndef Y_Memory_StaticBuffer_Included
#define Y_Memory_StaticBuffer_Included 1

#include "y/memory/buffer/rw.hpp"
#include "y/libc/block/zero.h"
namespace Yttrium
{
    namespace Memory
    {

        template <size_t N>
        class StaticBuffer : public ReadWriteBuffer
        {
        public:
            inline explicit StaticBuffer() noexcept :
            addr(0),
            data()
            {
                Coerce(addr) = Y_BZero(data);
            }

            inline virtual ~StaticBuffer() noexcept
            {
            }

            inline virtual const void * ro()     const noexcept { return addr; }
            inline virtual size_t       length() const noexcept { return N;    }

        private:
            void * const addr;
            char         data[N];
        };


    }

}

#endif // !Y_Memory_StaticBuffer_Included
