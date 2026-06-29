
#include "y/chemical/type/ikey.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        IKey:: ~IKey() noexcept
        {

        }

        size_t       IKey:: length() const noexcept { return bytes; }

        const void * IKey:: ro()     const noexcept
        {
            return &ask(1);
        }
    }

}
