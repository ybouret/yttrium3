

#include "y/cameo/product/queued.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;

Y_UTEST(cameo_product_queued)
{

    const float           f = 1.0f/90.2f;        Y_PRINTV(Cameo::Product::Pith::GetRank(f));
    const XReal<float>    x = 1.0f/90.2f;        Y_PRINTV(Cameo::Product::Pith::GetRank(x));
    const Complex<double> z(1,-2);               Y_PRINTV(Cameo::Product::Pith::GetRank(z));
    const Complex< XReal<long double> > Z(2,-1); Y_PRINTV(Cameo::Product::Pith::GetRank(Z));

    {
        Cameo::Product::Queued<float> cp;
        cp << 10.0f << -200.0f << 3.0f << 0.0001f;
        std::cerr << cp << std::endl;
        std::cerr << cp() << std::endl;
    }


}
Y_UDONE()


