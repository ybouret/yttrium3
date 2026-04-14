
//! \file

#ifndef Y_Libc_InputFile_Included
#define Y_Libc_InputFile_Included 1

#include "y/libc/file.hpp"
#include "y/libc/stdin.hpp"
#include "y/string/fwd.hpp"
#include <cstdio>

namespace Yttrium
{
    namespace Libc
    {

        class InputFile : public File
        {
        public:
            explicit InputFile(const char * const);
            explicit InputFile(const Core::String<char> &);
            explicit InputFile(const StdIn_ &);
            virtual ~InputFile() noexcept;

        private:
            Y_Disable_Copy_And_Assign(InputFile);
        };

    }

}

#endif // !Y_Libc_InputFile_Included

