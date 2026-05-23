#include "y/mkl/algebra/rank.hpp"
#include "y/utest/run.hpp"
#include "y/random/type-gen.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(algebra_rank)
{

    Core::Rand ran;
    
    for(size_t n=1;n<=10;++n)
    {
        for(size_t m=1;m<=20;++m)
        {
            Matrix<int> M(n,m);
            Random::Generate::Matrix(ran,M);
        }
    }

}
Y_UDONE()

