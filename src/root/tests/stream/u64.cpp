#include "y/stream/io/encode64.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/format/hexadecimal.hpp"


namespace Yttrium {

    namespace IO
    {
        class Decode64 : public U64Bits
        {
        public:
            explicit Decode64(const uint8_t b, const char * const varName);
            virtual ~Decode64() noexcept;

            const size_t numExtra;

        private:
            Y_Disable_Copy_And_Assign(Decode64);
        };

        Decode64:: Decode64(const uint8_t b, const char * const varName) :
        numExtra(b)
        {
            Coerce(numExtra) >>= SourceBits;

            if(numExtra>Size)
            {
                Specific::Exception excp("IO::Decode64","too many extra bytes");
                if(varName) excp.cat("for '%s'", varName);
                throw excp;
            }
            std::cerr << "numExtra=" << numExtra << std::endl;
        }

        Decode64:: ~Decode64() noexcept
        {

        }

    }
}

using namespace Yttrium;


Y_UTEST(stream_u64)
{
    Core::Rand ran;

    Y_PRINTV(IO::U64Bits::Size);
    Y_PRINTV(IO::U64Bits::HeaderBits);
    Y_PRINTV(IO::U64Bits::SourceBits);
    Y_PRINTV(IO::U64Bits::SourceMask);
    

    for(size_t i=0;i<=64;++i)
    {
        for(size_t iter=0;iter<4;++iter)
        {
            const uint64_t qw = ran.gen<uint64_t>(i);
            IO::Encode64   enc64(qw);
            std::cerr << Hexadecimal(qw) << " =>" << enc64 << std::endl;

            const uint8_t * u = (const uint8_t *)enc64.ro();
            IO::Decode64 dec64(u[0],0); Y_ASSERT(dec64.numExtra == enc64.length() -1 );


        }
    }


}
Y_UDONE()

