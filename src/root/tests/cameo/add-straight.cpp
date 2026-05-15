#include "y/cameo/add/straight.hpp"
#include "y/utest/run.hpp"
#include "y/apex/rational.hpp"

using namespace Yttrium;

Y_UTEST(cameo_add_straight)
{

    Cameo::StraightSummator<apn> nsum;
    Cameo::StraightSummator<apz> zsum;
    Cameo::StraightSummator<apq> qsum;

    for(unsigned i=1;i<=4;++i)
    {
        nsum << i;
        zsum << (int)i;
        qsum << (int)i;
    }

    std::cerr << nsum() << " " << zsum() << " " << qsum() << std::endl;


}
Y_UDONE()
