

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

        //______________________________________________________________________
        //
        //
        //
        //! Wrapper for output file
        //
        //
        //______________________________________________________________________
        class OutputFile : public File
        {
        public:

            explicit OutputFile(const char * const, const bool append=false);          //!< open regular file or Y_STD[OUT|ERR] \param append append iff true
            explicit OutputFile(const Core::String<char> &, const bool append=false);  //!< open regular file or Y_STD[OUT|ERR] \param append append iff true
            explicit OutputFile(const StdOut_ &); //!< get stdout
            explicit OutputFile(const StdErr_ &); //!< get stderr
            virtual ~OutputFile() noexcept;       //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

        private:
            Y_Disable_Copy_And_Assign(OutputFile); //!< discarded
        };

        

    }

}

#endif // !Y_Libc_OutputFile_Included

