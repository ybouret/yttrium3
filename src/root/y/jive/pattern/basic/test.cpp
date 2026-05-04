#include "y/jive/pattern/basic/all.hpp"

namespace Yttrium
{
    namespace Jive
    {
        bool Pattern:: isBasic() const noexcept
        {
            switch(uuid)
            {
                case Any1:: UUID:
                case Byte:: UUID:
                case Lump:: UUID:
                case Excluded:: UUID:
                    return true;
                default:
                    break;
            }
            return false;
        }

    }
}
