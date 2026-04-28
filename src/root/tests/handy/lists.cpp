#include "y/core/list.hpp"
#include "y/container/sequence.hpp"
#include "y/container.hpp"
#include "y/ability/lockable.hpp"

namespace Yttrium
{
    namespace Handy
    {

        template <
        typename                           NODE,
        template <typename,typename> class CACHE,
        typename                           THREADING_POLICY
        >
        class ListProto
        {
        public:
            typedef NODE                         NodeType;
            typedef typename NodeType::ParamType ParamType;
            typedef Core::ListOf<NODE>           CoreType;
            typedef typename NodeType::Type      Type;
            typedef typename NodeType::ConstType ConstType;

            inline explicit ListProto() : list(), cache()
            {
            }

            inline explicit ListProto(const ListProto &other) : list(), cache(other.cache)
            {
                Y_Lock(*cache);
                try
                {
                    for(const NodeType *node=other.list.head;node;node=node->next)
                        list.pushTail(cache->mirror(node));
                }
                catch(...) { free_(); throw; }
            }

            inline virtual ~ListProto() noexcept { free_(); }

            inline friend std::ostream & operator<<(std::ostream &os, const ListProto &self)
            {
                return os << self.list;
            }

            inline size_t size()     const noexcept { return list.size; }

            inline void popTail() noexcept
            {
                Y_Lock(*cache);
                cache->banish( list.popTail() );
            }

            inline void popHead() noexcept
            {
                Y_Lock(*cache);
                cache->banish( list.popTail() );
            }

            inline void pushTail(ParamType args)
            {
                Y_Lock(*cache);
                list.pushTail( cache->summon(args) );
            }

            inline void pushHead(ParamType args)
            {
                Y_Lock(*cache);
                list.pushHead( cache->summon(args) );
            }

            inline ListProto & operator<<(ParamType args)
            {
                pushTail(args); return *this;
            }

            inline ListProto & operator>>(ParamType args)
            {
                pushHead(args); return *this;
            }

            inline virtual void free() noexcept { free_(); }



            inline Type &      head()       noexcept { assert(list.head); return **list.head; }
            inline Type &      tail()       noexcept { assert(list.tail); return **list.tail; }
            inline ConstType & head() const noexcept { assert(list.head); return **list.head; }
            inline ConstType & tail() const noexcept { assert(list.tail); return **list.tail; }

            inline ListProto & operator<<( const ListProto & other )
            {
                { ListProto tmp(other); list.mergeTail(tmp.list); }
                return *this;
            }

            inline ListProto & operator>>( const ListProto & other )
            {
                { ListProto tmp(other); list.mergeHead(tmp.list); }
                return *this;
            }



        protected:
            Core::ListOf<NODE>           list;

        public:
            CACHE<NODE,THREADING_POLICY> cache;

        private:
            Y_Disable_Assign(ListProto);
            inline void free_() noexcept
            {
                Y_Lock(*cache);
                while( list.size ) cache->banish( list.popTail() );
            }



        };

    }
}



#include "y/handy/cache/shared.hpp"
#include "y/handy/cache/direct.hpp"
#include "y/utest/run.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/handy/node/light.hpp"
#include "y/handy/node/heavy.hpp"
#include "y/core/rand.hpp"
#include "y/container/sequence/vector.hpp"

using namespace Yttrium;

template <typename T>
static inline void testProto( Core::Rand &ran )
{
    typedef Handy::LightNode<T> Node;
    const size_t n = ran.in<size_t>(5,10);
    Vector<T>    v(WithAtLeast,n);
    for(size_t i=0;i<n;++i) v << T( ran.in<int>(-10,10) );

    std::cerr << "v=" << v << std::endl;

    {
        Handy::ListProto<Node,Handy::DirectCache,SingleThreadedClass> list;
        for(size_t i=v.size();i>0;--i)
        {
            if( ran.tails() ) list << v[i]; else list >> v[i];
        }

        std::cerr << list << std::endl;
    }



}


Y_UTEST(handy_lists)
{
    Core::Rand ran;
    testProto<int>(ran);

}
Y_UDONE()

