
#include "y/counting/partition.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(counting_part)
{
    Partition part(7);

    do
    {
        std::cerr << part << std::endl;
    } while( part.next() );

    part.boot();


}
Y_UDONE()


