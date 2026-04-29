
#include "y/handy/plain/light/list.hpp"
#include "y/utest/run.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/threading/multi-threaded-object.hpp"


using namespace Yttrium;

Y_UTEST(handy_plain_light_list)
{

    Handy::PlainLightList<int,SingleThreadedClass> stl;
    Handy::PlainLightList<int,MultiThreadedObject> mtl;
}
Y_UDONE()

