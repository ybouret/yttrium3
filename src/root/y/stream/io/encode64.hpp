
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

        class Encode64 : public U64Bits, public Memory::ReadOnlyBuffer
        {
        public:
            static const size_t Request = 1 + Size;

            explicit Encode64(uint64_t qw) noexcept;
            virtual ~Encode64() noexcept;

            virtual const void * ro() const noexcept;
            virtual size_t       length() const noexcept;
        private:
            Y_Disable_Copy_And_Assign(Encode64);
            size_t          nOut;
            uint8_t * const byte;
            void *          wksp[ Alignment::WordsGEQ<Request>::Count ];
        };
    }
}

#endif // !Y_Stream_IO_Encode64_Included

