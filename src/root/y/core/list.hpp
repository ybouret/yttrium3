

//! \file

#ifndef Y_Core_List_Included
#define Y_Core_List_Included

#include "y/core/linked.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Core
    {
        //! helper to check node to insert
#define Y_Core_List_Check(node) \
/**/ assert(0!=node);           \
/**/ assert(0==node->next);     \
/**/ assert(0==node->prev);     \
/**/ assert(!owns(node))

        //! helper to check empty list
#define Y_Core_List_CheckEmpty(L) \
/**/ assert(0==(L).size);         \
/**/ assert(0==(L).head);         \
/**/ assert(0==(L).tail)




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
            // Definitions
            //
            //__________________________________________________________________
            inline explicit ListOf() noexcept : LinkedType(), tail(0) {} //!< setup
            inline virtual ~ListOf() noexcept { assert(0==tail); }       //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! push a new node at tail \param node a valid node \return inserted node
            inline NODE * pushTail(NODE * const node) noexcept
            {
                Y_Core_List_Check(node);
                switch(size) {
                    case 0: Coerce(head) = Coerce(tail) = node; break;
                    default:
                        assert(0!=tail);
                        tail->next   = node;
                        node->prev   = tail;
                        Coerce(tail) = node;
                }
                ++Coerce(size);
                return node;
            }

            //! push a new node at head \param node a valid node \return inserted node
            inline NODE * pushHead(NODE * const node) noexcept
            {
                Y_Core_List_Check(node);
                switch(size) {
                    case 0: Coerce(head) = Coerce(tail) = node; break;
                    default:
                        assert(0!=head);
                        head->prev   = node;
                        node->next   = head;
                        Coerce(head) = node;
                }
                ++Coerce(size);
                return node;
            }

            //! pop tail node \return extracted tail
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

            //! pop head node \return extracted head
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


            //! pop owned node \param node node in list \return extracted node
            inline NODE * pop(NODE * const node) noexcept
            {
                assert( owns(node) );
                if(node==head)
                    return popHead();
                else
                {
                    if(node==tail)
                        return popTail();
                    else
                    {
                        assert(size>2);
                        assert(head!=tail);
                        assert(head->next!=tail);
                        assert(tail->prev!=head);
                        NODE * const prev = node->prev;
                        NODE * const next = node->next;
                        node->next = 0;
                        node->prev = 0;
                        prev->next = next;
                        next->prev = prev;
                        --Coerce(size);
                        return node;
                    }
                }
            }

            //! fetch const node \param indx in [1:size] \return node pointer
            const NODE * fetch(size_t indx) const noexcept
            {
                assert(indx>=1);
                assert(indx<=size);
                if(indx<= (size>>1) )
                {
                    const NODE *node = head;
                    while(--indx>0) node=node->next;
                    return node;
                }
                else
                {
                    const NODE *node = tail;
                    indx = size-indx;
                    while(indx-- > 0) node=node->prev;
                    return node;
                }
            }

            //! fetch node \param indx in [1:size] \return node pointer
            NODE * fetch(const size_t indx) noexcept
            {
                const ListOf &self = *this;
                return (NODE *)self.fetch(indx);
            }

            //! exchange contents \param rhs another list
            inline void  swapForList(ListOf &rhs) noexcept
            {
                this->swapForLinked(rhs);
                CoerceSwap(tail,rhs.tail);
            }

            //! merge content at tail \param rhs another list \return *this
            ListOf & mergeTail(ListOf &rhs) noexcept
            {
                ListOf &lhs = *this; assert( &lhs != &rhs );
                if(lhs.size<=0)
                {
                    if(rhs.size>0)
                        lhs.swapForList(rhs);
                }
                else
                {
                    assert(lhs.size>0);
                    if(rhs.size>0)
                    {
                        // attach lhs.tail <-> rhs.head
                        lhs.tail->next = rhs.head;
                        rhs.head->prev = lhs.tail;

                        // update lhs
                        Coerce(lhs.tail)  = rhs.tail;
                        Coerce(lhs.size) += rhs.size;

                        // update rhs
                        rhs.hardReset();
                    }
                }

                return *this;
            }

            //! merge content at head \param rhs another list \return *this
            ListOf & mergeHead(ListOf &rhs) noexcept
            {
                (void) rhs.mergeTail(*this); Y_Core_List_CheckEmpty(*this);
                swapForList(rhs);
                return *this;
            }

            //! divide content into two lists
            /**
             \param lhs empty list, will contain first half
             \param rhs empty list, will contain second half
             */
            void divide(ListOf &lhs, ListOf &rhs) noexcept
            {
                Y_Core_List_CheckEmpty(lhs);
                Y_Core_List_CheckEmpty(rhs);
                switch(size)
                {
                    case 0: return;
                    case 1: swapForList(lhs); return;
                    default:
                        break;
                }
                // select first half
                NODE *       node = head;
                const size_t half = size>>1; assert(half>0);
                for(size_t i=half-1;i>0;--i)
                {
                    node=node->next;
                }
                // split node <-> peer
                NODE * const peer = node->next;
                peer->prev = 0;
                node->next = 0;

                // assign lhs
                Coerce(lhs.head) = head;
                Coerce(lhs.tail) = node;
                Coerce(lhs.size) = half;

                // assign rhs
                Coerce(rhs.head) = peer;
                Coerce(rhs.tail) = tail;
                Coerce(rhs.size) = size-half;

                // finalize this
                hardReset();
            }

            //! fusion of two lists int this
            /**
             \param lhs left list
             \param rhs right list
             \param compareNodes nodes comparison
             */
            template <typename COMPARE_NODES> inline
            void fusion(ListOf &lhs, ListOf &rhs, COMPARE_NODES &compareNodes)
            {
                Y_Core_List_CheckEmpty(*this);
                while(lhs.size>0 && rhs.size>0) {
                    const NODE * const L = lhs.head; assert(L);
                    const NODE * const R = rhs.head; assert(R);
                    pushTail( (compareNodes(L,R) < 0) ? lhs.popHead() : rhs.popHead() );
                }
                mergeTail(lhs);
                mergeTail(rhs);
            }


            //! merge sort
            /**
             \param compareNodes nodes comparison
             */
            template <typename COMPARE_NODES> inline
            void sort(COMPARE_NODES &compareNodes)
            {
                if(size<=1) return;
                ListOf lhs,rhs;
                divide(lhs,rhs); assert(0==size);
                try
                {
                    lhs.sort(compareNodes);
                    rhs.sort(compareNodes);
                    fusion(lhs,rhs,compareNodes);
                }
                catch(...)
                {
                    mergeHead(lhs);
                    mergeTail(rhs);
                    throw;
                }
            }

            //! sort by increasing nodes address
            inline void sortByIncreasingAddress()
            {
                sort(ByIncreasingNodeAddress);
            }

            //! sort by increasing nodes address
            inline void sortByDecreasingAddress()
            {
                sort(ByDecreasingNodeAddress);
            }


#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            template <typename COMPARISON>
            struct CompareBy
            {
                COMPARISON * comparison;
                inline int operator()(const NODE * const lhs, const NODE * const rhs)
                {
                    return (*comparison)(**lhs,**rhs);
                }
            };
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

            //! sort by data comparision \param comparison compatible comparison
            template <typename COMPARISON>
            inline void sortBy(COMPARISON &comparison)
            {
                CompareBy<COMPARISON> cmp = { &comparison };
                sort(cmp);
            }


            //! insertion after a node
            /**
             \param mine one of my node
             \param node source node
             \return inserted node after mine
             */
            inline NODE * insertAfter(NODE * const mine, NODE * const node) noexcept
            {
                Y_Core_List_Check(node); assert(mine); assert(size>0); assert( owns(mine) );
                if(tail==mine)
                {
                    // push tail
                    tail->next   = node;
                    node->prev   = tail;
                    Coerce(tail) = node;
                }
                else
                {
                    assert(size>=2); assert(tail!=head); assert(0!=mine->next);
                    NODE * const next = mine->next;
                    node->prev = mine;
                    node->next = next;
                    mine->next = node;
                    next->prev = node;
                }
                ++Coerce(size);
                return node;
            }

            //! insertion before a node
            /**
             \param mine one of my node
             \param node source node
             \return inserted node before mine
             */
            inline NODE * insertBefore(NODE * const mine, NODE * const node) noexcept
            {
                Y_Core_List_Check(node); assert(mine); assert(size>0); assert( owns(mine) );
                if(head==mine)
                {
                    head->prev   = node;
                    node->next   = head;
                    Coerce(head) = node;
                }
                else
                {
                    assert(size>=2); assert(tail!=head); assert(0!=mine->prev);
                    NODE * const prev = mine->prev;
                    node->next = mine;
                    node->prev = prev;
                    mine->prev = node;
                    prev->next = node;
                }
                ++Coerce(size);
                return node;
            }

            //! move a node towards head
            /**
             \param node one of my node
             \return node exchanged with its prev
             */
            inline NODE * towardsHead(NODE * const node) noexcept
            {
                assert(owns(node));
                assert(head!=node);
                assert(size>=2);
                assert(0!=node->prev);
                NODE * const prev = node->prev;
                return insertBefore(prev,pop(node));
            }

            //! move owned no to head \param node one of list node \return node moved to head of list
            inline NODE * moveToHead(NODE * const node) noexcept
            {
                assert(owns(node));
                assert(head!=0);
                assert(size>0);
                return head != node ? pushHead( pop(node) ) : node;
            }

            //! insert a node in an ordered list \param node a new node \return inserted node at its ordered position
            inline NODE *insertByIncreasingAddress(NODE * const node) noexcept
            {
                Y_Core_List_Check(node);
                (void) pushTail(node);
                while(node && node->prev>node) (void) towardsHead(node);
                assert(this->hasIncreasingAddresses());
                return node;
            }
            
            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            NODE * const tail; //!< tail node


        protected:
            //! nodes comparison
            /**
             \param lhs first node
             \param rhs second node
             \return address difference
             */
            static inline
            ptrdiff_t ByIncreasingNodeAddress(const NODE * const lhs,
                                              const NODE * const rhs) noexcept {
                return lhs-rhs;
            }

            //! nodes comparison
            /**
             \param lhs first node
             \param rhs second node
             \return address difference
             */
            static inline
            ptrdiff_t ByDecreasingNodeAddress(const NODE * const lhs,
                                              const NODE * const rhs) noexcept {
                return rhs-lhs;
            }

            //! reset all data
            inline void hardReset() noexcept
            {
                Coerce(head) = 0;
                Coerce(tail) = 0;
                Coerce(size) = 0;
            }

        private:
            Y_Disable_Copy_And_Assign(ListOf); //!< discarded
        };

    }

}

#endif // !Y_Core_List_Included
