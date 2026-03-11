//! \file

#ifndef Y_Core_Linked_Included
#define Y_Core_Linked_Included


#include "y/config/setup.hpp"
#include <cassert>
#include <iostream>

namespace Yttrium
{
    namespace Core
    {
        template <typename NODE>
        class Linked
        {
        public:
            inline explicit Linked() noexcept : size(0), head(0)
            {
            }

            inline virtual ~Linked() noexcept
            {
                assert(0==head);
                assert(0==size);
            }

            inline bool owns(const NODE * const node) const noexcept
            {
                for(const NODE * mine=head;mine;mine=mine->next)
                    if(node==mine) return true;
                return false;
            }

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


            const size_t size;
            NODE * const head;

        private:
            Y_Disable_Copy_And_Assign(Linked);
        };
    }
}

#endif // !Y_Core_Linked_Included

