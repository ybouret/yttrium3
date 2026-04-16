

#include "y/apex/rational.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Apex
    {
        void Rational:: reduce()
        {
            if( denom.is0() ) throw Libc::Exception(EDOM,"%s with zero denominator", CallSign);
            Natural::Reduce(Coerce(numer.n),Coerce(denom));
        }
    }

}


