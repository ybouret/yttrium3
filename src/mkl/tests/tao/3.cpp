
#include "y/mkl/tao/3.hpp"
#include "y/utest/run.hpp"

#include "y/container/cxx/array.hpp"
#include "y/core/rand.hpp"
#include "y/random/type-gen.hpp"

using namespace Yttrium;

Y_UTEST(tao3)
{
    Concurrent::Engine seqEngine = Concurrent::SIMD::Sequential();
    Concurrent::Engine parEngine = Concurrent::SIMD::InParallel(0);

    MKL::Tao::Device seq(seqEngine);
    MKL::Tao::Device par(parEngine);
    Core::Rand       ran;

    const size_t nr = 4;
    const size_t nc = 3;
    Cameo::Addenda<double> addenda;
    Matrix<double>         A(nr,nc);
    Matrix<double>         B(nr,nc);
    for(size_t nx=1;nx<=8;++nx)
    {
        Matrix<double> lhs(nr,nx);
        Matrix<double> rhs(nx,nc);
        Random::Generate::Matrix(ran,lhs);
        Random::Generate::Matrix(ran,rhs);


        MKL::Tao::MMul(seq,A,lhs,rhs,addenda);
        std::cerr << "lhs=" << lhs << std::endl;
        std::cerr << "rhs=" << rhs << std::endl;
        std::cerr << "A=" << A << "-lhs*rhs" << std::endl;

        MKL::Tao::MMul(par,B,lhs,rhs,addenda);
        std::cerr << "B=" << B << "-lhs*rhs" << std::endl;

        break;
    }

}
Y_UDONE()

