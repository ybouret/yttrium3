
#include "y/jive/char.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Char:: ~Char() noexcept
        {
        }


        uint8_t & Char:: operator*() noexcept
        {
            return data;
        }

        const uint8_t & Char:: operator*() const noexcept
        {
            return data;
        }

        Char:: Char(const Char &ch) noexcept :
        LightObject(),
        Spot( (Spot&)ch),
        data(ch.data),
        next(0),
        prev(0)
        {
        }

        Char:: Char(const Spot &spot, const uint8_t c) noexcept :
        LightObject(),
        Spot( spot ),
        data( c ),
        next(0),
        prev(0)
        {

        }

    }

}
