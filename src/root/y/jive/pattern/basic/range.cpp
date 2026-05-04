#include "y/jive/pattern/basic/range.hpp"
#include "y/stream/output.hpp"
#include "y/jive/pattern/leading.hpp"
#include "y/string/format.hpp"
#include "y/ascii/printable.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Range:: Range(const uint8_t lo,
                      const uint8_t up) noexcept :
        OneChar(UUID),
        Within(lo,up)
        {
        }

        Range:: Range(const Within w) noexcept :
        OneChar(UUID),
        Within(w)
        {
        }
        

        Range:: Range(const Range &_) noexcept :
        OneChar(_), Within(_)
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

        void Range:: glean(Leading &leading) const noexcept
        {
            leading.set(*this);
        }

        bool Range:: univocal() const noexcept
        {
            return upper<=lower;
        }

        OutputStream & Range:: viz(OutputStream &fp) const
        {
            nodeName(fp) << '[';
            const String label = Formatted::Get("[%s-%s]", ASCII::Printable::Char[lower], ASCII::Printable::Char[upper]);
            fp << "label=\"" << label << "\",shape=rectangle";
            return Endl(fp<<']');
        }
    }

}
