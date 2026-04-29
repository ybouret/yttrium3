
#include "y/jive/pattern/basic/any1.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Any1:: Any1() noexcept : Pattern(UUID)
        {
        }

        Any1:: Any1(const Any1 &_) noexcept : Pattern(_) {}

        Pattern * Any1:: clone() const
        {
            return new Any1(*this);
        }

        bool Any1:: takes(Token &token, Source &source) const
        {
            Char * const ch = source.get();
            if(ch)
            {
                token << ch;
                return true;
            }
            else
            {
                return false;
            }
        }

        Any1:: ~Any1() noexcept
        {
        }
        


    }

}
