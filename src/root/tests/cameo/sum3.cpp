
#include "y/cameo/sum3.hpp"
#include "y/utest/run.hpp"


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

}
Y_UDONE()
