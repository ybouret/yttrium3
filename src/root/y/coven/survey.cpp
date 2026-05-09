
#include "y/coven/survey.hpp"

namespace Yttrium
{

    namespace Coven
    {

        Survey:: Survey() noexcept : Proxy<const Vectors>(), list()
        {
        }

        Survey:: ~Survey() noexcept
        {
        }

        const Vectors & Survey:: locus() const noexcept { return list; }

    }

}
