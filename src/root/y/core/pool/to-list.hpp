//! \file

#ifndef Y_Core_Pool_To_List_Included
#define Y_Core_Pool_To_List_Included 1

#include "y/core/pool.hpp"
#include "y/core/list.hpp"

namespace Yttrium
{
    namespace Core
    {

        //! converting pool to list
        struct PoolToList
        {
            //! make a list from a pool
            /**
             \param list an empty list
             \param pool source pool
             \return list
             */
            template <typename LIST, typename POOL> static inline
            LIST & Make(LIST &list, POOL &pool) noexcept
            {
                Y_Core_List_CheckEmpty(list);
                switch(pool.size)
                {
                    case 0: goto RETURN;
                    case 1:
                        Coerce(list.head) = Coerce(list.tail) = pool.head;
                        Coerce(list.size) = 1;
                        goto ZPOOL;
                    default: break;
                }

                {
                    assert(pool.size>=2);
                    typename POOL::NodeType *last = Coerce(list.head) = pool.head;
                    while(last->next)
                    {
                        last->next->prev=last;
                        last = last->next;
                    }
                    assert(0!=last);
                    Coerce(list.tail) = last;
                    Coerce(list.size) = pool.size;
                }

            ZPOOL:
                Coerce(pool.head) = 0;
                Coerce(pool.size) = 0;
            RETURN:
                return list;
            }

        };

    }
}

#endif // !Y_Core_Pool_To_List_Included

