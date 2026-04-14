#include "y/apex/n/code.hpp"
#include "y/apex/k/dec.hpp"

namespace Yttrium
{
    namespace Apex
    {
        String Natural:: toDec() const
        {
            assert(code);
            return KegDec::ToString<_Keg::Word,_Keg::Core>(*static_cast<const KegType *>(code));
        }
    }
}
