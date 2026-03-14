//! \file

#ifndef Y_Core_Pool_To_List_Included
#define Y_Core_Pool_To_List_Included 1

#include "y/core/pool.hpp"
#include "y/core/list.hpp"

namespace Yttrium
{
    namespace Core
    {

        struct PoolToList
        {
            template <typename LIST, typename POOL> static inline
            LIST & Make(LIST &list, POOL &pool) noexcept
            {
                return list;
            }

        };

    }
}

#endif // !Y_Core_Pool_To_List_Included

