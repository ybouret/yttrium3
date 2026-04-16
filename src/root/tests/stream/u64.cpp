#include "y/stream/io/decode64.hpp"
#include "y/stream/io/encode64.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/format/hexadecimal.hpp"

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
        for(size_t iter=0;iter<32;++iter)
        {
            const uint64_t qw = ran.gen<uint64_t>(i);
            IO::Encode64   enc64(qw);
            std::cerr << Hexadecimal(qw) << " => " << enc64;

            const uint8_t * u = (const uint8_t *)enc64.ro();
            IO::Decode64 dec64(u[0],0,0);
            Y_ASSERT(dec64.numExtra == enc64.length() -1 );
            for(size_t k=1;k<enc64.length();++k)
            {
                dec64(u[k],0,0);
            }
            std::cerr << " => " << dec64;
            std::cerr << std::endl;
            Y_ASSERT(dec64.value == qw);
        }
    }


}
Y_UDONE()

