//! \file

#ifndef Y_Libc_File_Included
#define Y_Libc_File_Included 1

#include "y/config/setup.hpp"
#include <cstdio>

namespace Yttrium
{
    namespace Libc
    {

        class File
        {
        public:

            explicit File(FILE * const fp, const bool mustClose) noexcept;
            virtual ~File() noexcept;


            FILE * const handle;
            const bool   closeDown;

        private:
            Y_Disable_Copy_And_Assign(File);
        };

    }
}

#endif // !Y_Libc_File_Included

