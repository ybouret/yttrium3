


//! \file

#ifndef Y_Handy_PlainHeavyList_Included
#define Y_Handy_PlainHeavyList_Included 1

#include "y/handy/plain/list.hpp"
#include "y/handy/node/heavy.hpp"


namespace Yttrium
{
    namespace Handy
    {
        //______________________________________________________________________
        //
        //
        //
        //! Plain List of heavy nodes
        //
        //
        //______________________________________________________________________
        template <typename T, typename THREADING_POLICY>
        class PlainHeavyList : public PlainList<HeavyNode<T>,THREADING_POLICY>
        {
        public:
            inline explicit PlainHeavyList()          {} //!< setup
            inline virtual ~PlainHeavyList() noexcept {} //!< cleanup

            //! duplicate \param L another list
            inline PlainHeavyList(const PlainHeavyList &L) :
            PlainList<HeavyNode<T>,THREADING_POLICY>(L)
            {
            }


        private:
            Y_Disable_Assign(PlainHeavyList); //!< discarded
        };

    }
}

#endif // !Y_Handy_PlainHeavyList_Included

