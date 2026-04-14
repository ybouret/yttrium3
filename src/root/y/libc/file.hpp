//! \file

#ifndef Y_Libc_File_Included
#define Y_Libc_File_Included 1

#include "y/object.hpp"
#include "y/memory/buffer/rw.hpp"
#include "y/pointer/auto.hpp"

#include <cstdio>

namespace Yttrium
{
    namespace Libc
    {

        class File : public Object
        {
        public:
            typedef Memory::ReadWriteBuffer BufferType;
            typedef AutoPtr<BufferType>     BufferPtr;

            explicit File(FILE * const fp, const bool mustClose) noexcept;
            virtual ~File() noexcept;

            FILE * const handle;
        protected:
            const bool   closeDown;
            BufferPtr    buffer;

            void      bufferize(); // called in constructor when required

        private:
            Y_Disable_Copy_And_Assign(File);
            void autoClose() noexcept;
        };

    }
}

#endif // !Y_Libc_File_Included

