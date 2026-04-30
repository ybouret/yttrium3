#include "y/string.hpp"
#include "y/stream/libc/output.hpp"
#include "y/stream/libc/input.hpp"
#include "y/utest/run.hpp"
#include "y/apex/rational.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(stream_serialize)
{
    Core::Rand ran;
    const String s = "Hello, World!";
    const apn    n(ran,ran.in<size_t>(10,100));

    Y_PRINTV(s);
    Y_PRINTV(n.toHex());


    size_t written = 0;
    {
        OutputFile fp("serialize.bin");
        {
            written += s.serialize(fp);
        }
        Y_PRINTV(written);
        {
            written += n.serialize(fp);
        }
        Y_PRINTV(written);
    }

    {
        InputFile fp("serialize.bin");
        {
            const String readString = String::Read(fp,"string");
            Y_PRINTV(readString);
            Y_ASSERT(s==readString);
        }
        {
            const apn readAPN = apn::Read(fp,"apn");
            Y_PRINTV(readAPN.toHex());
            Y_ASSERT(n==readAPN);
        }
    }
}
Y_UDONE()



