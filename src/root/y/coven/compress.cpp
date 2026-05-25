#include "y/coven/compress.hpp"

namespace Yttrium
{
    
    namespace Coven
    {
        size_t Compress:: CountNonZeroIn(const Readable<apz> &a) noexcept
        {
            size_t count = 0;
            for(size_t i=a.size();i>0;--i)
                if( __Zero__ != a[i].s) ++count;
            return count;
        }
    }
}
