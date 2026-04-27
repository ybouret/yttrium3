
#include "y/counting/partition.hpp"
#include "y/utest/run.hpp"
#include "y/ascii/convert.hpp"

using namespace Yttrium;

Y_UTEST(counting_part)
{
    size_t n = 7;
    if(argc>1) n = ASCII::Convert::To<size_t>(argv[1],"argv",0);
    Partition part(n);

    do
    {
        std::cerr << part << std::endl;
    } while( part.next() );

    part.boot();


}
Y_UDONE()


