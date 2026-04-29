
#include "y/jive/pattern/basic/any1.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Any1:: Any1() noexcept : OneChar(UUID)
        {
        }

        Any1:: Any1(const Any1 &_) noexcept : OneChar(_) {}

        Pattern * Any1:: clone() const
        {
            return new Any1(*this);
        }

        
        Any1:: ~Any1() noexcept
        {
        }
        

        bool Any1:: found(const uint8_t) const noexcept
        {
            return true;
        }
    }

}
