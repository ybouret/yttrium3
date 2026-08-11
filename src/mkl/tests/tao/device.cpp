#include "y/mkl/tao/device.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(tao_device)
{
    Concurrent::Engine seqEngine = Concurrent::SIMD::Sequential();
    Concurrent::Engine parEngine = Concurrent::SIMD::InParallel(0);

    MKL::Tao::Device seq(seqEngine);
    MKL::Tao::Device par(parEngine);
    


}
Y_UDONE()

