#include "y/mkl/algebra/ortho-space.hpp"
#include "y/utest/run.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(algebra_ortho_space)
{
    Core::Rand ran;

    Matrix<apz> Q;
    for(size_t m=2;m<=4;++m)
    {
        for(size_t n=1;n<m;++n)
        {
            Matrix<int> P(n,m);

            for(size_t i=1;i<=n;++i)
                for(size_t j=1;j<=m;++j)
                    P[i][j] = ran.in<int>(-5,5);

            std::cerr << "P=" << P << std::endl;

            if(MKL::OrthoSpace::Get(Q,P))
            {
                std::cerr << "Q=" << Q << std::endl;
            }
            else
            {
                std::cerr << "bad rank !" << std::endl;
            }

        }
    }

}
Y_UDONE()

