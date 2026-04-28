

#include "y/handy/basic/heavy/list.hpp"
#include "y/utest/run.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/threading/multi-threaded-object.hpp"



using namespace Yttrium;

Y_UTEST(handy_basic_heavy_list)
{

    Handy::BasicHeavyList<int,SingleThreadedClass> stl;
    Handy::BasicHeavyList<int,MultiThreadedObject> mtl;

}
Y_UDONE()

