
#include "y/cameo/product/direct.hpp"
#include "y/utest/run.hpp"

#include "y/apex/rational.hpp"

using namespace Yttrium;

Y_UTEST(cameo_product_direct)
{

    { Cameo::Product::Direct<apq> cs; Cameo::Product::Direct<apq> tmp(cs); }
    { Cameo::Product::Direct<apn> cs; }
    { Cameo::Product::Direct<apz> cs; }

}
Y_UDONE()


