#include "y/counting/permutation.hpp"
#include "y/utest/run.hpp"
#include "y/ascii/convert.hpp"

using namespace Yttrium;

Y_UTEST(counting_perm)
{
    size_t n = 6;
    if(argc>1) n = ASCII::Convert::To<size_t>(argv[1],"argv",0);
    Permutation perm(n);

    do
    {
        std::cerr << perm << std::endl;
    } while( perm.next() );

    perm.boot();


}
Y_UDONE()


