#include "y/counting/permutation.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(counting_perm)
{
    Permutation perm(5);

    do
    {
        std::cerr << perm << std::endl;
    } while( perm.next() );

    perm.boot();


}
Y_UDONE()


