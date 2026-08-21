
#include "y/mkl/tao/2.hpp"
#include "y/utest/run.hpp"

#include "y/container/cxx/array.hpp"
#include "y/core/rand.hpp"
#include "y/random/type-gen.hpp"

using namespace Yttrium;

Y_UTEST(tao2)
{
    Concurrent::Engine seqEngine = Concurrent::SIMD::Sequential();
    Concurrent::Engine parEngine = Concurrent::SIMD::InParallel(0);

    MKL::Tao::Device seq(seqEngine);
    MKL::Tao::Device par(parEngine);
    Core::Rand       ran;

    const size_t nr = 4;
    const size_t nc = 3;
    Matrix<double>         A(nr,nc);
    CxxArray<double>       lhs(nr);
    CxxArray<double>       lhsSeq(nr);
    CxxArray<double>       lhsPar(nr);
    CxxArray<double>       rhs(nc);
    Cameo::Addenda<double> addenda;

    Random::Generate::Array(ran,rhs);
    Random::Generate::Matrix(ran,A);

    std::cerr << "A=" << A << std::endl;
    std::cerr << "rhs=" << rhs << std::endl;
    std::cerr << std::endl;

    lhs.ld(0); A.mul(lhs,rhs);
    std::cerr << "lhs   =" << lhs << std::endl;

    lhsSeq.ld(0); MKL::Tao::Mul(seq,lhsSeq,A,rhs,addenda); std::cerr << "lhsSeq=" << lhsSeq << std::endl;
    lhsPar.ld(0); MKL::Tao::Mul(par,lhsPar,A,rhs,addenda); std::cerr << "lhsPar=" << lhsPar << std::endl;


}
Y_UDONE()

