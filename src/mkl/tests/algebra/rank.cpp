#include "y/mkl/algebra/rank.hpp"
#include "y/utest/run.hpp"
#include "y/random/type-gen.hpp"
#include "y/core/rand.hpp"
#include "y/core/min.hpp"

using namespace Yttrium;

Y_UTEST(algebra_rank)
{

    Core::Rand ran;
    
    for(size_t n=1;n<=5;++n)
    {
        for(size_t m=1;m<=10;++m)
        {
            std::cerr << n << "x" << m << std::endl;
            Matrix<int> M(n,m);
            Random::Generate::Matrix(ran,M);
            const size_t rank = MKL::Rank::Of(M);
            Y_ASSERT(rank <= Min(n,m) );
        }
    }

}
Y_UDONE()

