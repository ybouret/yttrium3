


#include "y/jive/pattern/basic/excluded.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Excluded:: Excluded(const uint8_t b) noexcept : OneChar(UUID), code(b)
        {
        }

        Excluded:: Excluded(const Excluded &_) noexcept : OneChar(_), code(_.code) {}

        Pattern * Excluded:: clone() const
        {
            return new Excluded(*this);
        }



        Excluded:: ~Excluded() noexcept
        {
        }

        bool Excluded:: found(const uint8_t b) const noexcept
        {
            return b != code;
        }

        size_t Excluded:: serialize(OutputStream &fp) const
        {
            const size_t res = emitUUID(fp);
            return res + fp.cbr(code);
        }
    }

}
