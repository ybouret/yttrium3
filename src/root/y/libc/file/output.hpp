

//! \file

#ifndef Y_Libc_OutputFile_Included
#define Y_Libc_OutputFile_Included 1

#include "y/libc/file.hpp"
#include "y/libc/stdout.hpp"
#include "y/libc/stderr.hpp"
#include "y/string/fwd.hpp"
#include <cstdio>

namespace Yttrium
{
    namespace Libc
    {

        class OutputFile : public File
        {
        public:
            explicit OutputFile(const char * const, const bool append=false);
            explicit OutputFile(const Core::String<char> &, const bool append=false);
            explicit OutputFile(const StdOut_ &);
            explicit OutputFile(const StdErr_ &);
            virtual ~OutputFile() noexcept;

        private:
            Y_Disable_Copy_And_Assign(OutputFile);
        };

    }

}

#endif // !Y_Libc_OutputFile_Included

