
#include "y/handy/basic/light/list.hpp"
#include "y/utest/run.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/threading/multi-threaded-object.hpp"



using namespace Yttrium;

Y_UTEST(handy_basic_light_list)
{

    Handy::BasicLightList<int,SingleThreadedClass> stl;
    Handy::BasicLightList<int,MultiThreadedObject> mtl;

}
Y_UDONE()

