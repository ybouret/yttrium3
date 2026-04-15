
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
        //______________________________________________________________________
        //
        //
        //
        //! Wrapper for input file
        //
        //
        //______________________________________________________________________
        class InputFile : public File
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit InputFile(const char * const);         //!< open regular file or Y_STDIN
            explicit InputFile(const Core::String<char> &); //!< open regular file of Y_STDIN
            explicit InputFile(const StdIn_ &);             //!< find stdin
            virtual ~InputFile() noexcept;                  //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! query single char
            /**
             \param C output
             \return true iff not EOF, throw exception upon error
             */
            bool     query(char &C);

            //! query block of data
            /**
             \param blockAddr memory
             \param blockSize request
             \return read bytes in blockAddr
             */
            size_t   query(void * const blockAddr, const size_t blockSize);

        private:
            Y_Disable_Copy_And_Assign(InputFile); //!< discarded
        };

    }

}

#endif // !Y_Libc_InputFile_Included

