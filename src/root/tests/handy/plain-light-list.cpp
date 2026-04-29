
#include "y/handy/plain/list.hpp"
#include "y/utest/run.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/threading/multi-threaded-object.hpp"
#include "y/handy/node/light.hpp"


using namespace Yttrium;

Y_UTEST(handy_plain_light_list)
{

    Handy::PlainList< Handy::LightNode<int>, SingleThreadedClass> stl;
    //Handy::BasicLightList<int,SingleThreadedClass> stl;
    //Handy::BasicLightList<int,MultiThreadedObject> mtl;
    stl.release();
}
Y_UDONE()

