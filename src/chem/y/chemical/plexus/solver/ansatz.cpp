

#include "y/chemical/plexus/solver/ansatz.hpp"

namespace Yttrium
{
    namespace Chemical
    {


        Ansatz:: Ansatz(const Equilibrium & _eq,
                        const xreal_t     & _eK,
                        const Aftermath   & _am,
                        const XReadable   & _cc) noexcept :
        eq(_eq),
        eK(_eK),
        am(_am),
        cc(_cc)
        {
        }

        Ansatz:: Ansatz(const Ansatz &_) noexcept :
        eq(_.eq),
        eK(_.eK),
        am(_.am),
        cc(_.cc)
        {
        }

        Ansatz:: ~Ansatz() noexcept
        {}


        SignType Ansatz:: IncreasingAX(const Ansatz &lhs, const Ansatz &rhs) noexcept
        {
            switch( Sign::Of(lhs.am.nz,rhs.am.nz) )
            {
                case Positive: return Negative;
                case Negative: return Positive;
                case __Zero__: break;
            }
            return Sign::Of(lhs.am.ax,rhs.am.ax);
        }

    }

}
