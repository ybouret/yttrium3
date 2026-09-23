#include "y/chemical/plexus/reactor/resources.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Resources:: ~Resources() noexcept
        {
        }

        Resources:: Resources(const size_t N, const size_t M) :
        finder( new Coven::Finder(M) ),
        minimize(),
        algebra( new Algebra(N,M) )
        {
        }

    }
}

