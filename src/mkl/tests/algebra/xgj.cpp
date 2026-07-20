#include "y/mkl/algebra/xgj.hpp"
#include "y/mkl/algebra/lu.hpp"
#include "y/utest/run.hpp"
#include "y/random/type-gen.hpp"
#include "y/core/rand.hpp"
#include "y/container/cxx/array.hpp"

using namespace Yttrium;
using namespace MKL;

Y_UTEST(algebra_xgj)
{
    Core::Rand ran;

    for(size_t n=1;n<=6;++n)
    {
        for(size_t iter=0;iter<8;++iter)
        {
            Matrix<apq> a(n,n);
            Matrix<apq> b(n,3);
            for(size_t i=1;i<=a.rows;++i)
            {
                for(size_t j=1;j<=a.cols;++j)
                {
                    a[i][j] = Random::Gen<uint8_t>::Get(ran);
                }

                for(size_t j=1;j<=b.cols;++j)
                {
                    b[i][j] = Random::Gen<uint8_t>::Get(ran);
                }
            }
            std::cerr << "a=" << a << std::endl;
            std::cerr << "b=" << b << std::endl;

            Matrix<apq> aa(a), bb(b);
            const size_t rk = XGJ::Build(aa,bb);
            std::cerr << "aa=" << aa << std::endl;
            std::cerr << "bb=" << bb << std::endl;

            if( n == rk )
            {
                LU<apq>       lu(n);
                CxxArray<apq> tmp(n);
                if(!lu.build(a)) throw Exception("unexpected singular matrix a");
                lu.solve(a,b,tmp);

                if(!lu.build(aa)) throw Exception("unexpected singular matrix aa");
                lu.solve(aa,bb,tmp);

                std::cerr << "x  = " << b  << std::endl;
                std::cerr << "xx = " << bb << std::endl;
                Y_CHECK(b==bb);
            }
        }

    }


}
Y_UDONE()
