//! \file

#ifndef Y_Core_Linked_Included
#define Y_Core_Linked_Included


#include "y/config/setup.hpp"
#include "y/swap.hpp"
#include <cassert>
#include <iostream>

namespace Yttrium
{
    namespace Core
    {
        //______________________________________________________________________
        //
        //
        //
        //! Base class for linked structures
        //
        //
        //______________________________________________________________________
        template <typename NODE>
        class Linked
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            inline explicit Linked() noexcept : size(0), head(0) {}

            //! cleanup
            inline virtual ~Linked() noexcept
            {
                assert(0==head);
                assert(0==size);
            }

            //! display
            inline friend std::ostream & operator<<(std::ostream &os, const Linked &self)
            {
                os << '[';
                const NODE * node = self.head;
                if(node) {
                    os << *node;
                    for(node=node->next;node;node=node->next)
                        os << ';' << *node;
                }
                os << ']';
                return os;
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! check ownership of a node
            /**
             \param node node to test
             \return true iff node is linked to this
             */
            inline bool owns(const NODE * const node) const noexcept
            {
                for(const NODE * mine=head;mine;mine=mine->next)
                    if(node==mine) return true;
                return false;
            }


            //! check nodes have increasing address \return true if that's the case
            inline bool hasIncreasingAddresses() const noexcept
            {
                for(const NODE *node=head;node;node=node->next) {
                    if(node->next && node->next<node) return false;
                }
                return true;
            }

            //! check nodes have decreasing address \return true if that's the case
            inline bool hasDecreasingAddresses() const noexcept
            {
                for(const NODE *node=head;node;node=node->next) {
                    if(node->next && node->next>node) return false;
                }
                return true;
            }

        protected:

            //! exchange variables \param rhs another lisy
            inline void swapForLinked(Linked &rhs) noexcept
            {
                CoerceSwap(size,rhs.size);
                CoerceSwap(head,rhs.head);
            }


        public:
            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________

            const size_t size; //!< number of owned nodes
            NODE * const head; //!< head node

        private:
            Y_Disable_Copy_And_Assign(Linked); //!< discarded
        };
    }
}

#endif // !Y_Core_Linked_Included

