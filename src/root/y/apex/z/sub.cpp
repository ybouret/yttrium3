#include "y/apex/integer.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Integer Integer:: operator-() const
        {
            Integer z = *this;
            Sign::MakeOpposite( Coerce(z.s) );
            return z;
        }
    }

}

