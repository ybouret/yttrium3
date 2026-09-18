
#include "y/chemical/plexus/solver/assets.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        Assets:: ~Assets() noexcept
        {
        }


        Assets:: Assets(const size_t n, const size_t m) :
        minimize(),
        algebra( new Algebra(n,m) ),
        finder(  new Coven::Finder(m) )
        {
        }

    }

}
