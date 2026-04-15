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

        //______________________________________________________________________
        //
        //
        //
        //! Wrapper for FILE *
        //
        //
        //______________________________________________________________________
        class File : public Object
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Memory::ReadWriteBuffer BufferType; //!< alias
            typedef AutoPtr<BufferType>     BufferPtr;  //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup with
            /**
             \param fp        file pointer, may be NULL if post-created
             \param mustClose set closeDoens
             */
            explicit File(FILE * const fp, const bool mustClose) noexcept;
            virtual ~File() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            FILE * const handle; //!< file ahndle
        protected:
            const bool   closeDown; //!< close when destructed
            BufferPtr    buffer;    //!< optional buffer

            void      bufferize();  //!< called in constructor when required

        private:
            Y_Disable_Copy_And_Assign(File); //!< discarded
            void autoClose() noexcept;       //!< take action when closing time
        };

    }
}

#endif // !Y_Libc_File_Included

