

//! \file

#ifndef Y_Core_List_Included
#define Y_Core_List_Included


#include "y/core/linked.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Core
    {
#define Y_Core_List_Check(node) \
/**/ assert(0!=node);           \
/**/ assert(0==node->next);     \
/**/ assert(0==node->prev);     \
/**/ assert(!owns(node))

        //______________________________________________________________________
        //
        //
        //
        //! simple list of nodes
        //
        //
        //______________________________________________________________________
        template <typename NODE>
        class ListOf : public Linked<NODE>
        {
        public:
            typedef Linked<NODE> LinkedType;
            typedef NODE         NodeType;
            using LinkedType::size;
            using LinkedType::head;
            using LinkedType::owns;

            inline explicit ListOf() noexcept : LinkedType(), tail(0)
            {
            }

            inline virtual ~ListOf() noexcept
            {
                assert(0==tail);
            }

            inline NODE * pushTail(NODE * const node) noexcept
            {
                Y_Core_List_Check(node);
                switch(size) {
                    case 0: Coerce(head) = Coerce(tail) = node; break;
                    default:
                        tail->next   = node;
                        node->prev   = tail;
                        Coerce(tail) = node;
                }
                ++Coerce(size);
                return node;
            }

            inline NODE * pushHead(NODE * const node) noexcept
            {
                Y_Core_List_Check(node);
                switch(size) {
                    case 0: Coerce(head) = Coerce(tail) = node; break;
                    default:
                        head->prev   = node;
                        node->next   = head;
                        Coerce(head) = node;
                }
                ++Coerce(size);
                return node;
            }

            inline NODE * popTail() noexcept
            {
                assert(0!=tail); assert(size>0);
                NODE * const node = tail;
                if(size<=1)
                {
                    Coerce(tail) = Coerce(head) = 0;
                }
                else
                {
                    Coerce(tail) = node->prev;
                    tail->next = 0;
                    node->prev = 0;
                }
                --Coerce(size);
                Y_Core_List_Check(node);
                return node;
            }

            inline NODE *popHead() noexcept
            {
                assert(0!=head); assert(size>0);
                NODE * const node = head;
                if(size<=1)
                {
                    Coerce(tail) = Coerce(head) = 0;
                }
                else
                {
                    Coerce(head) = node->next;
                    head->prev = 0;
                    node->next = 0;
                }
                --Coerce(size);
                Y_Core_List_Check(node);
                return node;
            }


            NODE * const tail;



        private:
            Y_Disable_Copy_And_Assign(ListOf);
        };

    }

}

#endif // !Y_Core_List_Included
