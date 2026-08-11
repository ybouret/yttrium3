
#include "y/concurrent/api/local/memory.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(concurrent_local_cache)
{

    Concurrent::LocalMemory mem = 0;

    mem->ensure(10,8);

    Y_PRINTV(mem->length());

}
Y_UDONE()

