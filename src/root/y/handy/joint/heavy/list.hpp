

//! \file

#ifndef Y_Handy_JointHeavyList_Included
#define Y_Handy_JointHeavyList_Included 1

#include "y/handy/list-proto.hpp"
#include "y/handy/node/heavy.hpp"
#include "y/handy/cache/shared.hpp"


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
        class JointHeavyList : public ListProto< HeavyNode<T>, SharedCache, THREADING_POLICY>
        {
        public:
            typedef SharedCache<HeavyNode<T>,THREADING_POLICY> CacheType;

            //! setup
            inline explicit JointHeavyList( const CacheType &sc ) :
            ListProto< HeavyNode<T>, SharedCache, THREADING_POLICY>(sc)
            {}

            inline virtual ~JointHeavyList() noexcept {} //!< cleanup

            //! duplicate \param L another list
            inline JointHeavyList(const JointHeavyList &L) :
            ListProto< HeavyNode<T>, SharedCache, THREADING_POLICY>(L)
            {
            }


        private:
            Y_Disable_Assign(JointHeavyList); //!< discarded
        };

    }
}

#endif // !Y_Handy_JointLightList_Included

