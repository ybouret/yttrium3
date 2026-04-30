#include "y/jive/pattern/basic/range.hpp"
#include "y/swap.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Range:: Range(const uint8_t lo,
                      const uint8_t up) noexcept :
        OneChar(UUID),
        lower(lo),
        upper(up)
        {
            if(up<lo) CoerceSwap(lo,up);
        }

        Range:: Range(const Range &_) noexcept :
        OneChar(_), lower(_.lower), upper(_.upper)
        {}

        Pattern * Range:: clone() const
        {
            return new Range(*this);
        }
        
        Range:: ~Range() noexcept
        {
        }

        bool Range:: found(const uint8_t b) const noexcept
        {
            return b>=lower && b <= upper;
        }

        size_t Range:: serialize(OutputStream &fp) const
        {
            size_t res = emitUUID(fp);
            res += fp.cbr(lower);
            res += fp.cbr(upper);
            return res;
        }
    }

}
