
#include "y/container/matrix.hpp"
#include "y/utest/run.hpp"

#include "y/random/type-gen.hpp"
#include "y/core/rand.hpp"

using namespace Yttrium;

Y_UTEST(algebra_mmul)
{
    Core::Rand ran;
    for(size_t nr=1;nr<=5;++nr)
    {
        for(size_t nc=1;nc<=5;++nc)
        {
            Matrix<apz> M(nr,nc);

            for(size_t nx=1;nx<=8;++nx)
            {
                Matrix<apz> a(nr,nx);
                Random::Generate::Matrix(ran,a);

                {
                    Matrix<apz> b(nx,nc);
                    Random::Generate::Matrix(ran,b);
                    M.mmul(a,b);

                    Matrix<apz> c(nx,nr);
                    Random::Generate::Matrix(ran,c);
                    M.mmul(TransposeOf,c,b);
                }

                {
                    Matrix<apz> b(nc,nx);
                    Random::Generate::Matrix(ran,b);
                    M.mmul(a,TransposeOf,b);
                }

                if(M.isSquare()) M.gram(a);

            }
        }
    }

}
Y_UDONE()

