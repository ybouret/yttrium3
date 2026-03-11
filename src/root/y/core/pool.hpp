
//! \file

#ifndef Y_Core_Pool_Included
#define Y_Core_Pool_Included


#include "y/core/linked.hpp"

namespace Yttrium
{
    namespace Core
    {
        //______________________________________________________________________
        //
        //
        //
        //! simple pool of nodes
        //
        //
        //______________________________________________________________________
        template <typename NODE>
        class PoolOf : public Linked<NODE>
        {
        public:
            typedef Linked<NODE> LinkedType;
            typedef NODE         NodeType;
            using LinkedType::size;
            using LinkedType::head;
            using LinkedType::owns;

            inline explicit PoolOf() noexcept : LinkedType() {}
            inline virtual ~PoolOf() noexcept {}

            inline NODE * query() noexcept
            {
                assert(size>0); assert(0!=head);
                NODE * const node = head;
                --Coerce(size);
                Coerce(head) = node->next;
                node->next   = 0;
                return node;
            }

            inline void store(NODE * const node) noexcept
            {
                assert(0!=node);
                assert(0==node->next);
                assert(!owns(node));
                node->next = head;
                Coerce(head) = node;
                ++Coerce(size);
            }



        private:
            Y_Disable_Copy_And_Assign(PoolOf);
        };

    }

}

#endif // !Y_Core_Pool_Included

