

//! \file

#ifndef Y_Handy_PlainLigthList_Included
#define Y_Handy_PlainLigthList_Included 1

#include "y/handy/plain/list.hpp"
#include "y/handy/node/light.hpp"


namespace Yttrium
{
    namespace Handy
    {
        //______________________________________________________________________
        //
        //
        //
        //! Plain List of light nodes
        //
        //
        //______________________________________________________________________
        template <typename T, typename THREADING_POLICY>
        class PlainLightList : public PlainList<LightNode<T>,THREADING_POLICY>
        {
        public:
            inline explicit PlainLightList()          {} //!< setup
            inline virtual ~PlainLightList() noexcept {} //!< cleanup

            //! duplicate \param L another list
            inline PlainLightList(const PlainLightList &L) :
            PlainList<LightNode<T>,THREADING_POLICY>(L)
            {
            }


        private:
            Y_Disable_Assign(PlainLightList); //!< discarded
        };

    }
}

#endif // !Y_Handy_PlainLigthList_Included

