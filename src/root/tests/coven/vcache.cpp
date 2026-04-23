


#include "y/coven/vcache.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(coven_vcache)
{
    Core::Rand    ran;

    for(size_t dims=1; dims <= 5; ++dims)
    {
        Coven::Metrics metrics(dims);
        Coven::VCache  vcache(metrics);
        
    }

}
Y_UDONE()

