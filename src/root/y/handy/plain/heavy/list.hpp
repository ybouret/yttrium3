


//! \file

#ifndef Y_Handy_PlainHeavyList_Included
#define Y_Handy_PlainHeavyList_Included 1

#include "y/handy/plain/list.hpp"
#include "y/handy/node/heavy.hpp"


namespace Yttrium
{
    namespace Handy
    {
        template <typename T, typename THREADING_POLICY>
        class PlainHeavyList : public PlainList<HeavyNode<T>,THREADING_POLICY>
        {
        public:
            inline explicit PlainHeavyList() {}

            inline PlainHeavyList(const PlainHeavyList &L) :
            PlainList<HeavyNode<T>,THREADING_POLICY>(L)
            {
            }

            inline virtual ~PlainHeavyList() noexcept {}

        private:
            Y_Disable_Assign(PlainHeavyList);
        };

    }
}

#endif // !Y_Handy_PlainHeavyList_Included

