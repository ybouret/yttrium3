
#include "y/chemical/plexus/reactor/algebra.hpp"

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
        nuT(n),
        xi(n)
        {
            for(size_t i=1;i<=n;++i)
            {
                J.append(i,i);
                dA.append(i,m);
                nu.append(i,m);
                nuT.append(m,i);
                xi.append(i);
            }
        }

        Algebra:: ~Algebra() noexcept
        {
        }

    }

}
