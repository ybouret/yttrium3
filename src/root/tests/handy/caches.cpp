#include "y/handy/cache/shared.hpp"
#include "y/handy/cache/direct.hpp"
#include "y/ability/caching.hpp"

#include "y/object/light.hpp"
#include "y/utest/run.hpp"

#include "y/threading/single-threaded-class.hpp"

#include "y/type/args.hpp"
#include "y/type/pulverize.hpp"


namespace Yttrium
{
    namespace Handy
    {

        template <typename T>
        class LightNode
        {
        public:
            Y_Args_Expose(T,Type);
            typedef T & ParamType;

            inline  LightNode(ParamType args) noexcept :
            data(args), next(0), prev(0) {}
            inline ~LightNode() noexcept {}

            inline Type      & operator*()       noexcept { return data; }
            inline ConstType & operator*() const noexcept { return data; }




        private:
            Y_Disable_Copy_And_Assign(LightNode);
            Type &      data;
        public:
            LightNode * next;
            LightNode * prev;
        };


        
        

    }
}

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

