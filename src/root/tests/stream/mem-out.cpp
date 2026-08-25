#include "y/stream/memory/output.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(stream_mem_out)
{

    OutputMemoryStream fp("memory stream");
    fp("Hello from %s@line %d", test, __LINE__);
    std::cerr << fp.data << std::endl;
    std::cerr << fp.data() << std::endl;
}
Y_UDONE()

