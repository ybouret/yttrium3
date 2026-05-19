#include "y/cameo/sum/direct.hpp"
#include "y/utest/run.hpp"

#include "y/apex/rational.hpp"

using namespace Yttrium;

Y_UTEST(cameo_sum_direct)
{
    { Cameo::Sum::Direct<apq> cs; Cameo::Sum::Direct<apq> tmp(cs); }
    { Cameo::Sum::Direct<apn> cs; }
    { Cameo::Sum::Direct<apz> cs; }

}
Y_UDONE()


