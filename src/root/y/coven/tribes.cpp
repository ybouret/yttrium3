
#include "y/coven/tribes.hpp"

namespace Yttrium
{

    namespace Coven
    {

        Tribes:: ~Tribes() noexcept
        {
        }

        Tribes:: Tribes() noexcept : list()
        {
        }

        const Tribe::List & Tribes:: locus() const noexcept
        {
            return list;
        }



    }
}
