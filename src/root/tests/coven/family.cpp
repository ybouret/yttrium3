#include "y/coven/family.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"
#include "y/core/min.hpp"

using namespace Yttrium;

Y_UTEST(coven_family)
{
    Core::Rand    ran;

    for(size_t dims=1; dims <= 4; ++dims)
    {
        std::cerr << "-- dimension = " << dims << std::endl;
        Coven::Metrics metrics(dims);
        Coven::VCache  vcache(metrics);
        Coven::Family  family(vcache);

        CxxArray<int>  a(dims);

        do
        {
            for(size_t i=dims;i>0;--i)
            {
                a[i] = ran.in<int>(-10,10);
            }
            Coven::Vector * v = family.accepted(a);
            if(v)
                family.grow(v);

        } while( family.list.size != dims );

        family.writeXML(std::cerr);

        std::cerr << std::endl;
    }

    Y_SIZEOF(Coven::Family);
}
Y_UDONE()

