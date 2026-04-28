#include "y/handy/cache/shared.hpp"
#include "y/handy/cache/direct.hpp"
#include "y/utest/run.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/handy/node/light.hpp"



using namespace Yttrium;

Y_UTEST(handy_caches)
{

    {
        typedef Handy::LightNode<int>                 iNode;
        Handy::DirectCache<iNode,SingleThreadedClass> iDCache;
        Handy::ObjectCache<iNode,SingleThreadedClass> iOCache;
        Handy::SharedCache<iNode,SingleThreadedClass> iSCache;

        int ref = 7;
        {
            iNode * node = iDCache->summon(ref);
            iDCache->banish(node);
        }

        {
            iNode * node = iOCache->summon(ref);
            iOCache->banish(node);
        }

        {
            iNode * node = iSCache->summon(ref);
            iSCache->banish(node);
        }


    }

}
Y_UDONE()

