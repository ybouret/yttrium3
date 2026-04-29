
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
        //______________________________________________________________________
        //
        //
        //
        //! Basic List of heavy nodes
        //
        //
        //______________________________________________________________________
        template <typename T, typename THREADING_POLICY>
        class BasicHeavyList : public ListProto< HeavyNode<T>, DirectCache, THREADING_POLICY>
        {
        public:

            inline explicit BasicHeavyList()          {} //!< setup
            inline virtual ~BasicHeavyList() noexcept {} //!< cleanup

            //! duplicate \param L another list
            inline BasicHeavyList(const BasicHeavyList &L) :
            ListProto< HeavyNode<T>, DirectCache, THREADING_POLICY>(L)
            {
            }


        private:
            Y_Disable_Assign(BasicHeavyList); //!< discarded
        };

    }
}

#endif // !Y_Handy_BasicHeavyList_Included

