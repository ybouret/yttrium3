#include "y/cameo/sum/vectorial.hpp"
#include "y/utest/run.hpp"
#include "y/mkl/complex.hpp"
#include "y/mkl/v3d.hpp"


using namespace Yttrium;



Y_UTEST(cameo_sum_vectorial)
{

    { Cameo::Sum::Vectorial<float,Complex<float>> cs; }
    { Cameo::Sum::Vectorial<double,V3D<double>> cs; }


}
Y_UDONE()


