#include "y/jive/pattern/basic/lump.hpp"
#include "y/stream/output.hpp"
#include "y/jive/pattern/leading.hpp"
#include "y/string/format.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Lump:: Lump(const uint8_t lo,
                    const uint8_t up) noexcept :
        OneChar(UUID),
        Within(lo,up)
        {
        }

        Lump:: Lump(const Within w) noexcept :
        OneChar(UUID),
        Within(w)
        {
        }


        Lump:: Lump(const Lump &_) noexcept :
        OneChar(_), Within(_)
        {}

        Pattern * Lump:: clone() const
        {
            return new Lump(*this);
        }

        Lump:: ~Lump() noexcept
        {
        }

        bool Lump:: found(const uint8_t b) const noexcept
        {
            return b>=lower && b <= upper;
        }

        size_t Lump:: serialize(OutputStream &fp) const
        {
            size_t res = emitUUID(fp);
            res += fp.cbr(lower);
            res += fp.cbr(upper);
            return res;
        }

        void Lump:: glean(Leading &leading) const noexcept
        {
            leading.set(*this);
        }

        bool Lump:: univocal() const noexcept
        {
            return upper<=lower;
        }

        OutputStream & Lump:: viz(OutputStream &fp) const
        {
            nodeName(fp) << '[';
            const String label = Formatted::Get("[%c-%c]", (char)lower, (char)upper );
            Label(fp,label) << ",shape=rectangle";
            //fp << "label=\"" << label << "\",shape=rectangle";
            return Endl(fp<<']');
        }

    }

}


#include "y/pointer/auto.hpp"
#include "y/jive/pattern/basic/byte.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Pattern * Lump:: optimized()
        {
            if(upper<=lower)
            {
                assert(lower==upper);
                AutoPtr<Pattern> p = new Byte(lower);
                delete this;
                return p.yield();
            }
            else
            {
                return this;
            }
        }


    }

}
