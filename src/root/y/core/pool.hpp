
//! \file

#ifndef Y_Core_Pool_Included
#define Y_Core_Pool_Included


#include "y/core/linked.hpp"

namespace Yttrium
{
    namespace Core
    {

        //! helper to check empty pool
#define Y_Core_Pool_CheckEmpty(L) \
/**/ assert(0==(L).size);         \
/**/ assert(0==(L).head)

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
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Linked<NODE> LinkedType; //!< alias
            typedef NODE         NodeType;   //!< alias
            using LinkedType::size;
            using LinkedType::head;
            using LinkedType::owns;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline explicit PoolOf() noexcept : LinkedType() {} //!< setup
            inline virtual ~PoolOf() noexcept                {} //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! query a node \return head node removed from this
            inline NODE * query() noexcept
            {
                assert(size>0); assert(0!=head);
                NODE * const node = head;
                --Coerce(size);
                Coerce(head) = node->next;
                node->next   = 0;
                return node;
            }

            //! store a node \param node a valid node \return stored node
            inline NODE * store(NODE * const node) noexcept
            {
                assert(0!=node);
                assert(0==node->next);
                assert(!owns(node));
                node->next   = head;
                Coerce(head) = node;
                ++Coerce(size);
                return node;
            }

            inline NODE * stash(NODE * const node) noexcept
            {
                assert(0!=node);
                assert(0==node->next);
                assert(0==node->next);
                if(size<=0)
                {
                    Coerce(head) = node;
                }
                else
                {
                    NODE *last = head;
                    while(last->next) last=last->next;
                    assert(0!=last);
                    assert(0==last->next);
                    last->next = node;
                }
                ++Coerce(size);
                return node;
            }


            //! exchange contents \param rhs another pool
            inline void swapForPool(PoolOf &rhs) noexcept
            {
                this->swapForLinked(rhs);
            }

        private:
            Y_Disable_Copy_And_Assign(PoolOf); //!< discarded
        };

    }

}

#endif // !Y_Core_Pool_Included

