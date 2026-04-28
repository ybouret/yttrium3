#include "y/handy/cache/direct.hpp"
#include "y/ability/caching.hpp"

#include "y/object/light.hpp"
#include "y/utest/run.hpp"

#include "y/threading/single-threaded-class.hpp"

#include "y/type/args.hpp"
#include "y/type/pulverize.hpp"
#include "y/core/pool.hpp"
#include "y/core/pool/to-list.hpp"
#include "y/core/list/to-pool.hpp"

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


        template <typename NODE, typename THREADING_POLICY>
        class ObjectCache : public THREADING_POLICY, public Caching
        {
        public:
            Y_HandyCache_Decl();
            typedef Core::PoolOf<NodeType> PoolType;
            typedef Core::ListOf<NodeType> ListType;

            inline explicit ObjectCache() :
            ThreadingPolicy(),
            Caching(),
            zpool()
            {

            }

            inline virtual ~ObjectCache() noexcept
            {
                release_();
            }


            inline virtual void   release()      noexcept { release_(); }
            inline virtual size_t count()  const noexcept { return zpool.size; }
            inline virtual void   cache(const size_t n)
            {
                Y_Must_Lock();
                for(size_t i=n;i>0;--i)
                    zpool.store( LightObject::AcquireZombie<NodeType>() );
            }

            inline virtual void gc(const uint8_t amount) noexcept
            {
                Y_Must_Lock();
                ListType zlist;
                Core::PoolToList::Make(zlist,zpool).sortByDecreasingAddress();
                {
                    const size_t newSize = NewSize(amount,zlist.size);
                    while(zlist.size>newSize)
                        LightObject::ReleaseZombie( zlist.popHead() );
                }
                Core::ListToPool::Make(zpool,zlist);
            }


            inline NodeType * summon(ParamType args) {
                Y_Must_Lock();
                NodeType * const node = zpool.size ? zpool.query() : LightObject::AcquireZombie<NodeType>();
                try { return new (node) NodeType(args); }
                catch(...) {
                    zpool.store( NodeAPI::Clear(node) );
                    throw;
                }
            }

            inline void banish(NodeType * const alive) noexcept
            {
                Y_Must_Lock();
                assert(alive);
                zpool.store( Pulverized(alive) );
            }

            inline void remove(NodeType * const alive) noexcept
            {
                Y_Must_Lock();
                assert(alive);
                LightObject::ReleaseZombie( Pulverized(alive) );
            }

            



        private:
            Y_Disable_Copy_And_Assign(ObjectCache);
            PoolType zpool;
            inline void release_() noexcept
            {
                Y_Must_Lock();
                while( zpool.size ) LightObject::ReleaseZombie( zpool.query() );
            }
        };



        //template <typename NODE> class DirectCache;
        //template <typename NODE> class SharedCache;
        //template <typename NODE> class ObjectCache;

    }
}

using namespace Yttrium;

Y_UTEST(handy_caches)
{

    {
        typedef Handy::LightNode<int>                 iNode;
        Handy::DirectCache<iNode,SingleThreadedClass> iDCache;
        Handy::ObjectCache<iNode,SingleThreadedClass> iOCache;

        int ref = 7;
        {
            iNode * node = iDCache.summon(ref);
            iDCache.banish(node);
        }

        {
            iNode * node = iOCache.summon(ref);
            iOCache.banish(node);
        }



    }

}
Y_UDONE()

