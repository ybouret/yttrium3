

#include "y/chemical/plexus/conservation/canon.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace Conservation
        {
            Canon:: ~Canon() noexcept
            {
            }

            Canon:: Canon(const Law &first) :
            Object(),
            LList(),
            next(0),
            prev(0)
            {
                pushTail(first);
            }
        }

    }

}
