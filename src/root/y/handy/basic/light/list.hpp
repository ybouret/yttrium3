//! \file

#ifndef Y_Handy_BasicLightList_Included
#define Y_Handy_BasicLightList_Included 1

#include "y/handy/list-proto.hpp"
#include "y/handy/node/light.hpp"
#include "y/handy/cache/direct.hpp"


namespace Yttrium
{
    namespace Handy
    {
        template <typename T, typename THREADING_POLICY>
        class BasicLightList : public ListProto< LightNode<T>, DirectCache, THREADING_POLICY>
        {
        public:
            inline explicit BasicLightList() {}

            inline BasicLightList(const BasicLightList &L) :
            ListProto< LightNode<T>, DirectCache, THREADING_POLICY>(L)
            {
            }

            inline virtual ~BasicLightList() noexcept {}
            
        private:
            Y_Disable_Assign(BasicLightList);
        };

    }
}

#endif // !Y_Handy_BasicLightList_Included

