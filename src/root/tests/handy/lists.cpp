#include "y/core/list.hpp"
#include "y/ability/releasable.hpp"

namespace Yttrium
{
    namespace Handy
    {

        template <
        typename                           NODE,
        template <typename,typename> class CACHE,
        typename                           THREADING_POLICY
        >
        class ListProto : public Releasable
        {
        public:
            typedef NODE                         NodeType;
            typedef typename NodeType::ParamType ParamType;
            typedef Core::ListOf<NODE>           CoreType;
            
            inline explicit ListProto() : list(), cache()
            {
            }

            inline virtual ~ListProto() noexcept {}

            

        protected:
            Core::ListOf<NODE>           list;

        public:
            CACHE<NODE,THREADING_POLICY> cache;

        private:
            Y_Disable_Copy_And_Assign(ListProto);

        };

    }
}



#include "y/handy/cache/shared.hpp"
#include "y/handy/cache/direct.hpp"
#include "y/utest/run.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/handy/node/light.hpp"
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

    {
        Handy::ListProto<Node,Handy::DirectCache,SingleThreadedClass> list;
    }

}


Y_UTEST(handy_lists)
{
    Core::Rand ran;
    testProto<int>(ran);

}
Y_UDONE()

