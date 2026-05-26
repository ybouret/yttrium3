#include "y/cameo/sum3.hpp"
#include "y/utest/run.hpp"
#include "y/mkl/complex.hpp"

using namespace Yttrium;


Y_UTEST(cameo_sum3)
{

    {
        Cameo::Sum3<int> s3;
        std::cerr << s3(1,-10,100) << std::endl;
    }

    {
        Cameo::Sum3<unsigned> s3;
        std::cerr << s3(1,10,100) << std::endl;
    }

    {
        Cameo::Sum3<apz> s3;
        std::cerr << s3(1,-10,100) << std::endl;
    }


    {
        Cameo::Sum3<float> s3;
        std::cerr << s3(1,-10,100) << std::endl;
    }

    {
        Cameo::Sum3< XReal<long double> > s3;
        std::cerr << s3(1,-10,100) << std::endl;
    }

    {
        Cameo::Sum3< Complex<float> > s3;
        std::cerr << s3( Complex<float>(1,2), Complex<float>(3,4), Complex<float>(5,6) ) << std::endl;
    }

}
Y_UDONE()
