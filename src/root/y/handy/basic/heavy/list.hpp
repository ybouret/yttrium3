
//! \file

#ifndef Y_Handy_BasicHeavyList_Included
#define Y_Handy_BasicHeavyList_Included 1

#include "y/handy/list-proto.hpp"
#include "y/handy/node/heavy.hpp"
#include "y/handy/cache/direct.hpp"


namespace Yttrium
{
    namespace Handy
    {
        template <typename T, typename THREADING_POLICY>
        class BasicHeavyList : public ListProto< HeavyNode<T>, DirectCache, THREADING_POLICY>
        {
        public:
            inline explicit BasicHeavyList() {}

            inline BasicHeavyList(const BasicHeavyList &L) :
            ListProto< HeavyNode<T>, DirectCache, THREADING_POLICY>(L)
            {
            }

            inline virtual ~BasicHeavyList() noexcept {}

        private:
            Y_Disable_Assign(BasicHeavyList);
        };

    }
}

#endif // !Y_Handy_BasicHeavyList_Included

