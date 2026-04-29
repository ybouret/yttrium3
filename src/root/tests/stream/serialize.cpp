#include "y/string.hpp"
#include "y/stream/libc/output.hpp"
#include "y/stream/libc/input.hpp"
#include "y/utest/run.hpp"
#include "y/apex/rational.hpp"

using namespace Yttrium;

Y_UTEST(stream_serialize)
{

    size_t written = 0;
    {
        OutputFile fp("serialize.bin");
        {
            const String s = "Hello, World!";
            written += s.serialize(fp);
        }
        Y_PRINTV(written);
        {
            const apn n = 0x1234567;
            written += n.serialize(fp);
        }
        Y_PRINTV(written);
    }

    {
        InputFile fp("serialize.bin");
        {
            const String readString = String::Read(fp,"string");
            Y_PRINTV(readString);
        }
    }
}
Y_UDONE()



