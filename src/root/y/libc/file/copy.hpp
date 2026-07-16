
//! \file

#ifndef Y_Libc_FileCopy_Included
#define Y_Libc_FileCopy_Included 1

#include "y/libc/file/input.hpp"
#include "y/libc/file/output.hpp"

namespace Yttrium
{
    namespace Libc
    {
        //! File Copy API
        struct FileCopy
        {
            //! copy input file to output file
            static void To(OutputFile &, InputFile &);

        };
    }

}

#endif // !Y_Libc_FileCopy_Included

