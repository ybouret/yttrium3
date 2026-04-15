#include "y/apex/integer.hpp"

namespace Yttrium
{
    namespace Apex
    {

        bool Integer:: Cmp(const Integer &lhs, const Integer &rhs)
        {
            switch( Sign::Pair(lhs.s,rhs.s) )
            {
                case Sign::ZZ:
                    break; // => zero
            }

            // zero
            return __Zero__;
        }

    }
}


