
//! \file

#ifndef Y_Stream_IO_Encode64_Included
#define Y_Stream_IO_Encode64_Included 1

#include "y/stream/io/u64.hpp"
#include "y/calculus/alignment.hpp"
#include "y/memory/buffer/ro.hpp"

namespace Yttrium
{
    namespace IO
    {

        //______________________________________________________________________
        //
        //
        //
        //! Encoding 64 bits to compact array
        //
        //
        //______________________________________________________________________
        class Encode64 : public U64Bits, public Memory::ReadOnlyBuffer
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const size_t Request = 1 + Size; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Encode64(uint64_t qw) noexcept; //!< encode \param qw 64 bits value
            virtual ~Encode64()            noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const void * ro()    const noexcept;
            virtual size_t       length() const noexcept;
        private:
            Y_Disable_Copy_And_Assign(Encode64); //!< discarded

            size_t          nOut; //!< produced bytes
            uint8_t * const byte; //!< content
            void *          wksp[ Alignment::WordsGEQ<Request>::Count ]; //!< workspace
        };
    }
}

#endif // !Y_Stream_IO_Encode64_Included

