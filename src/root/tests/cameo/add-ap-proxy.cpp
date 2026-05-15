#include "y/cameo/add/ap-proxy.hpp"
#include "y/utest/run.hpp"
#include "y/apex/rational.hpp"

using namespace Yttrium;

Y_UTEST(cameo_add_ap_proxy)
{

    Cameo::AP_ProxySummator<int>      isum;
    Cameo::AP_ProxySummator<uint16_t> usum;

    for(unsigned i=1;i<=4;++i)
    {
        isum << (int)i;
        usum << (uint16_t)i;
    }

    std::cerr << isum() << " " << usum() << std::endl;


}
Y_UDONE()

