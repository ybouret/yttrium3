

#include "y/cameo/product/raised.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;

Y_UTEST(cameo_product_raised)
{

    { Cameo::Product::Raised<int>   cp; Cameo::Product::Raised<int> tmp(cp); std::cerr << tmp << std::endl; }
    { Cameo::Product::Raised<uint16_t> cp; }


}
Y_UDONE()


