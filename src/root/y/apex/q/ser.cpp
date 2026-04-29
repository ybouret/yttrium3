


#include "y/apex/rational.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Apex
    {
        size_t Rational:: serialize(OutputStream &fp) const
        {
            const size_t res = numer.serialize(fp);
            return res + denom.serialize(fp);

        }
    }

}
