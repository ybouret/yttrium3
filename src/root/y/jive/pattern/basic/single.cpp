

#include "y/jive/pattern/basic/single.hpp"
#include "y/stream/output.hpp"
#include "y/jive/pattern/leading.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Single:: Single(const uint8_t b) noexcept : OneChar(UUID), code(b)
        {
        }

        Single:: Single(const Single &_) noexcept : OneChar(_), code(_.code) {}

        Pattern * Single:: clone() const
        {
            return new Single(*this);
        }



        Single:: ~Single() noexcept
        {
        }

        bool Single:: found(const uint8_t b) const noexcept
        {
            return b == code;
        }

        size_t Single:: serialize(OutputStream &fp) const
        {
            const size_t res = emitUUID(fp);
            return res + fp.cbr(code);
        }

        void Single:: glean(Leading &leading) const noexcept
        {
            leading << code;
        }

    }

}
