
#include "y/memory/plastic/forge.hpp"

namespace Yttrium
{

    namespace Memory
    {

        namespace Plastic
        {

            Forge:: Forge(Book     & userBook,
                          Lockable & userLock) noexcept :
            book(   userBook ),
            access( userLock )
            {
            }

            Forge:: ~Forge() noexcept
            {

            }
        }

    }

}
