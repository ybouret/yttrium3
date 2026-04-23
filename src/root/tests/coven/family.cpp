#include "y/coven/family.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(coven_family)
{
    Core::Rand    ran;

    for(size_t dims=1; dims <= 5; ++dims)
    {
        Coven::Metrics metrics(dims);
        Coven::VCache  vcache(metrics);
        Coven::Family  family(vcache);

        CxxArray<int>  a(dims);

        {
            for(size_t i=dims;i>0;--i)
            {
                a[i] = ran.in<int>(-10,10);
            }
            Coven::Vector * v = family.accepted(a);
            if(v) family.grow(v);
        }


    }

    Y_SIZEOF(Coven::Family);
}
Y_UDONE()

