//! \file

#ifndef Y_Memory_ReadOnlyBuffer_Included
#define Y_Memory_ReadOnlyBuffer_Included 1

#include "y/config/setup.hpp"
#include "y/ostream-proto.hpp"

namespace Yttrium
{
    namespace Memory
    {
        //______________________________________________________________________
        //
        //
        //
        //! Read Only Buffer interface
        //
        //
        //______________________________________________________________________
        class ReadOnlyBuffer
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit ReadOnlyBuffer() noexcept; //!< setup
            virtual ~ReadOnlyBuffer() noexcept; //!< cleanup
            Y_OSTREAM_PROTO(ReadOnlyBuffer);    //!< display

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            virtual const void * ro()     const noexcept = 0; //!< \return first byte address
            virtual size_t       length() const noexcept = 0; //!< \return available bytes




        private:
            Y_Disable_Copy_And_Assign(ReadOnlyBuffer); //!< discarded
        };
    }

}
#endif // !Y_Memory_ReadOnlyBuffer_Included


