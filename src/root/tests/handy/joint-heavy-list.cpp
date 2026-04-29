

#include "y/handy/joint/heavy/list.hpp"
#include "y/utest/run.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/threading/multi-threaded-object.hpp"



using namespace Yttrium;

Y_UTEST(handy_joint_heavy_list)
{
    Handy::JointHeavyList<int,SingleThreadedClass>::CacheType sc;
    Handy::JointHeavyList<int,MultiThreadedObject>::CacheType mc;

    Handy::JointHeavyList<int,SingleThreadedClass> stl(sc);
    Handy::JointHeavyList<int,MultiThreadedObject> mtl(mc);
}
Y_UDONE()

