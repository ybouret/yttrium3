
//! \file

#ifndef Y_Stream_IO_Decode64_Included
#define Y_Stream_IO_Decode64_Included 1

#include "y/stream/io/u64.hpp"
#include "y/ostream-proto.hpp"

namespace Yttrium
{
    namespace IO
    {
        class Decode64 : public U64Bits
        {
        public:
            static const char * const CallSign;

            explicit Decode64(const uint8_t b,
                              const char * const varName,
                              const char * const varPart);
            virtual ~Decode64() noexcept;
            Y_OSTREAM_PROTO(Decode64);

            bool ready() const noexcept;
            void operator()(const uint8_t b,
                            const char * const varName,
                            const char * const varPart);

            const uint64_t value;
            const size_t   numExtra;
            const size_t   expected;
            const size_t   dataBits;
        private:
            Y_Disable_Copy_And_Assign(Decode64);
        };
    }

}

#endif // !Y_Stream_IO_Decode64_Included
