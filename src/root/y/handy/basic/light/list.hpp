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
        //______________________________________________________________________
        //
        //
        //
        //! Basic List of light nodes
        //
        //
        //______________________________________________________________________
        template <typename T, typename THREADING_POLICY>
        class BasicLightList : public ListProto< LightNode<T>, DirectCache, THREADING_POLICY>
        {
        public:
            inline explicit BasicLightList()          {} //!< setup
            inline virtual ~BasicLightList() noexcept {} //!< cleanup

            //! duplicate \param L another list
            inline BasicLightList(const BasicLightList &L) :
            ListProto< LightNode<T>, DirectCache, THREADING_POLICY>(L)
            {
            }


        private:
            Y_Disable_Assign(BasicLightList); //!< discarded
        };

    }
}

#endif // !Y_Handy_BasicLightList_Included

