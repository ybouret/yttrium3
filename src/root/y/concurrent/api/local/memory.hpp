
//! \file

#ifndef Y_Concurrent_LocalMemory_Included
#define Y_Concurrent_LocalMemory_Included 1

#include "y/concurrent/api/local/cache.hpp"
#include "y/pointer/arc.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        typedef ArcPtr<LocalCache> SharedLocalCache; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Handle shared memory to dispatch to Subdivision
        //
        //
        //______________________________________________________________________
        class LocalMemory : public SharedLocalCache
        {
        public:
            LocalMemory(LocalCache * const);           //!< setup with given or new local cache
            LocalMemory(const LocalMemory &) noexcept; //!< duplicate, shared copy
            virtual ~LocalMemory()           noexcept; //!< cleanup

        private:
            Y_Disable_Assign(LocalMemory); //!< disable
        };

    }

}

#endif // !Y_Concurrent_LocalMemory_Included

