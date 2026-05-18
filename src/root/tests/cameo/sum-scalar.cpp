

#include "y/cameo/sum/scalar.hpp"
#include "y/utest/run.hpp"

#include "y/apex/rational.hpp"

using namespace Yttrium;

Y_UTEST(cameo_sum_scalar)
{

    { Cameo::Sum::Scalar<apq>           cs; std::cerr << cs.callSign() << std::endl; }
    { Cameo::Sum::Scalar<int>           cs; std::cerr << cs.callSign() << std::endl; }
    { Cameo::Sum::Scalar<uint16_t>      cs; std::cerr << cs.callSign() << std::endl; }
    { Cameo::Sum::Scalar<float>         cs; std::cerr << cs.callSign() << std::endl; }
    { Cameo::Sum::Scalar<XReal<double>> cs; std::cerr << cs.callSign() << std::endl; }


}
Y_UDONE()


