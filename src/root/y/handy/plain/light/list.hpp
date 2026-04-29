

//! \file

#ifndef Y_Handy_PlainLigthList_Included
#define Y_Handy_PlainLigthList_Included 1

#include "y/handy/plain/list.hpp"
#include "y/handy/node/light.hpp"


namespace Yttrium
{
    namespace Handy
    {
        template <typename T, typename THREADING_POLICY>
        class PlainLightList : public PlainList<LightNode<T>,THREADING_POLICY>
        {
        public:
            inline explicit PlainLightList() {}

            inline PlainLightList(const PlainLightList &L) :
            PlainList<LightNode<T>,THREADING_POLICY>(L)
            {
            }

            inline virtual ~PlainLightList() noexcept {}

        private:
            Y_Disable_Assign(PlainLightList);
        };

    }
}

#endif // !Y_Handy_PlainLigthList_Included

