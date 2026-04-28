#include "y/core/list.hpp"

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



using namespace Yttrium;

Y_UTEST(handy_lists)
{


}
Y_UDONE()

