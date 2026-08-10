
#include "y/concurrent/api/local-cache.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(concurrent_local_cache)
{

    Concurrent::LocalCache lc;

    lc.ensure(10,8);

    Y_PRINTV(lc.length());

}
Y_UDONE()

