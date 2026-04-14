
//! \file

#ifndef Y_Libc_FileBuffer_Included
#define Y_Libc_FileBuffer_Included 1


#include "y/object.hpp"
#include "y/memory/buffer/allocated.hpp"
#include "y/memory/allocator/archon.hpp"

namespace Yttrium
{
    namespace Libc
    {
        typedef Memory::AllocatedBuffer<Memory::Archon> FileBufferType;

        class FileBuffer : public Object, public FileBufferType
        {
        public:
            explicit FileBuffer();
            virtual ~FileBuffer() noexcept;
            
        private:
            Y_Disable_Copy_And_Assign(FileBuffer);
        };
    }
}

#endif // !Y_Libc_FileBuffer_Included

