
//! \file

#ifndef Y_Handy_JointLightList_Included
#define Y_Handy_JointLightList_Included 1

#include "y/handy/list-proto.hpp"
#include "y/handy/node/light.hpp"
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
        class JointLightList : public ListProto< LightNode<T>, SharedCache, THREADING_POLICY>
        {
        public:
            typedef SharedCache<LightNode<T>,THREADING_POLICY> CacheType;

            //! setup
            inline explicit JointLightList( const CacheType &sc ) :
            ListProto< LightNode<T>, SharedCache, THREADING_POLICY>(sc)
            {}

            inline virtual ~JointLightList() noexcept {} //!< cleanup

            //! duplicate \param L another list
            inline JointLightList(const JointLightList &L) :
            ListProto< LightNode<T>, SharedCache, THREADING_POLICY>(L)
            {
            }


        private:
            Y_Disable_Assign(JointLightList); //!< discarded
        };

    }
}

#endif // !Y_Handy_JointLightList_Included

