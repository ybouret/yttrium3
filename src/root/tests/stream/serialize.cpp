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
    const apn    n(ran,ran.in<size_t>(0,100));
    const apz    z(ran,ran.in<size_t>(0,40));
    const apq    q(ran,ran.in<size_t>(0,40),ran.in<size_t>(1,40));
    Y_PRINTV(s);
    Y_PRINTV(n.toHex());
    Y_PRINTV(z);
    Y_PRINTV(q);
    std::cerr << std::endl;

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
        {
            written += z.serialize(fp);
        }
        Y_PRINTV(written);
        {
            written += q.serialize(fp);
        }
        Y_PRINTV(written);
    }
    std::cerr << std::endl;

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
        {
            const apz readAPZ = apz::Read(fp,"apz");
            Y_PRINTV(readAPZ);
            Y_ASSERT(z==readAPZ);
        }
        {
            const apq readAPQ = apq::Read(fp,"apq");
            Y_PRINTV(readAPQ);
            Y_ASSERT(q==readAPQ);
        }
    }
}
Y_UDONE()



