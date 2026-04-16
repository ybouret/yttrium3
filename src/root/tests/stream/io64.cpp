#include "y/stream/libc/output.hpp"
#include "y/stream/libc/input.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(stream_io64)
{

    Core::Rand          ran;
    static uint64_t     entry[1000];
    static const size_t count = Y_Static_Size(entry);

    const String fileName = "io64.dat";
    std::cerr << "-- writing..." << std::endl;
    size_t       written = 0;
    {
        OutputFile fp(fileName);
        for(size_t i=0;i<count;++i)
        {
            entry[i] = ran.gen<uint64_t>( ran.in<size_t>(0,64) );
            written += fp.vbr64(entry[i]);
        }
    }
    std::cerr << "-- #written=" << written << " / " << sizeof(entry) << std::endl;

    std::cerr << "-- reading..." << std::endl;
    {
        InputFile fp(fileName);
        for(size_t i=0;i<count;++i)
        {
            const uint64_t qw = fp.vbr64(0,0);
            Y_ASSERT(qw==entry[i]);
        }
    }

}
Y_UDONE()

