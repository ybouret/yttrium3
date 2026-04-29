

#include "y/handy/joint/light/list.hpp"
#include "y/utest/run.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/threading/multi-threaded-object.hpp"



using namespace Yttrium;

Y_UTEST(handy_joint_light_list)
{
    Handy::JointLightList<int,SingleThreadedClass>::CacheType sc;
    Handy::JointLightList<int,MultiThreadedObject>::CacheType mc;

    Handy::JointLightList<int,SingleThreadedClass> stl(sc);
    Handy::JointLightList<int,MultiThreadedObject> mtl(mc);

}
Y_UDONE()

