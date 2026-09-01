
#include "y/coven/finder.hpp"

namespace Yttrium
{

    namespace Coven
    {

        Finder:: Finder(const size_t dims) :
        metrics(dims),
        vcache(metrics),
        family(vcache),
        size(family->size)
        {
        }

        
        Finder:: ~Finder() noexcept
        {
        }

        void Finder:: free() noexcept
        {
            family.free();
        }

    }

}
