
//! \file

#ifndef Y_Core_List_To_Pool_Included
#define Y_Core_List_To_Pool_Included 1

#include "y/core/pool.hpp"
#include "y/core/list.hpp"

namespace Yttrium
{
    namespace Core
    {

        //! converting list to pool
        struct ListToPool
        {
            //! make a pool from a list
            /**
             \param pool an empty pool
             \param list source list
             \return pool
             */
            template <typename POOL, typename LIST> static inline
            POOL & Make(POOL &pool, LIST &list) noexcept
            {
                Y_Core_Pool_CheckEmpty(pool);

                Coerce(pool.head) = list.head;
                Coerce(pool.size) = list.size;
                for(typename POOL::NodeType *node = pool.head;node;node=node->next)
                    node->prev = 0;
                Coerce(list.head) = 0;
                Coerce(list.tail) = 0;
                Coerce(list.size) = 0;
                return pool;
            }

        };

    }

}

#endif // !Y_Core_List_To_Pool_Included
