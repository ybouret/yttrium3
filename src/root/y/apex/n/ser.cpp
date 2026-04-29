
#include "y/apex/n/code.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Apex
    {
        size_t Natural:: serialize(OutputStream &fp) const
        {
            assert(code);
            const KegType &keg = *static_cast<const KegType *>(code);
            const size_t   num = keg.bytes;
            size_t res = fp.vbr(num);
            for(size_t i=0;i<num;++i)
            {
                const uint8_t b = keg.getByte(i);
                res += fp.cbr(b);
            }
            return res;
        }
    }

}
