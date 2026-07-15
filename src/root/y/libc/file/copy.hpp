
//! \file

#ifndef Y_Libc_FileCopy_Included
#define Y_Libc_FileCopy_Included 1

#include "y/libc/file/input.hpp"
#include "y/libc/file/output.hpp"

namespace Yttrium
{
    namespace Libc
    {
        struct FileCopy
        {
            static void To(OutputFile &, InputFile &);

        };
    }

}

#endif // !Y_Libc_FileCopy_Included

