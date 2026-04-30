


#include "y/jive/pattern/basic/excluded.hpp"

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

    }

}
