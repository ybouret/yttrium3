#include "y/handy/joint/set.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/threading/multi-threaded-object.hpp"


#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(handy_joint_set)
{
    typedef Handy::JointSet<int,SingleThreadedClass> ISet;
    typedef ISet::CacheType                          ICache;

    ICache sc;
    ISet   setA(sc);

    std::cerr << setA->size() << std::endl;
    std::cerr << setA << std::endl;
    setA << 1; std::cerr << setA << std::endl;
    setA << 0; std::cerr << setA << std::endl;
    setA << 2; std::cerr << setA << std::endl;

    Y_CHECK(setA->found(0));
    Y_CHECK(setA->found(1));
    Y_CHECK(setA->found(2));

    setA.insert( sc->summon(-7) ); std::cerr << setA << std::endl;

    setA.extract(1);
    

}
Y_UDONE()
