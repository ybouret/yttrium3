
#include "y/chemical/plexus/solver/algebra.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Algebra:: Algebra(const size_t n, const size_t m) :
        Object(),
        lu(n),
        J(n),
        dA(n),
        nu(n),
        nuT(n)
        {
            for(size_t i=1;i<=n;++i)
            {
                J.append(i,i);
                dA.append(i,m);
                nu.append(i,m);
                nuT.append(m,i);
            }
        }

        Algebra:: ~Algebra() noexcept
        {
        }

    }

}
