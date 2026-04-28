
#ifndef Y_Handy_Cache_Defs_Included
#define Y_Handy_Cache_Defs_Included 1

#include "y/handy/cache/defs.hpp"
#include "y/threading/must-lock.hpp"
#include "y/object/light.hpp"
#include "y/type/pulverize.hpp"
#include <cassert>

namespace Yttrium
{
    class Lockable;
    
    namespace Handy
    {

#define Y_HandyCache_Decl()                             \
typedef THREADING_POLICY               ThreadingPolicy; \
typedef NODE                           NodeType;        \
typedef typename NodeType::ParamType   ParamType;       \
typedef typename ThreadingPolicy::Lock Lock

        //! helper to ensure clear node
        struct NodeAPI
        {
            //! clear node next and prev \param node valid node \return cleared node
            template <typename NODE> static inline
            NODE * Clear(NODE * const node) noexcept
            {
                assert(node);
                node->next = 0;
                node->prev = 0;
                return node;
            }
        };

    }

}

#endif // !Y_Handy_Cache_Defs_Included
