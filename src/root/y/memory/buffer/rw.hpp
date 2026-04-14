
//! \file

#ifndef Y_Memory_ReadWriteBuffer_Included
#define Y_Memory_ReadWriteBuffer_Included 1

#include "y/memory/buffer/ro.hpp"

namespace Yttrium
{
    namespace Memory
    {
        //______________________________________________________________________
        //
        //
        //
        //! Read-Write Buffer interface
        //
        //
        //______________________________________________________________________
        class ReadWriteBuffer : public ReadOnlyBuffer
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit ReadWriteBuffer() noexcept; //!< setup
            virtual ~ReadWriteBuffer() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void * rw() noexcept; //!< \return address of first writable byte

        private:
            Y_Disable_Copy_And_Assign(ReadWriteBuffer); //!< discarded
        };
    }

}
#endif // !Y_Memory_ReadWriteBuffer_Included


