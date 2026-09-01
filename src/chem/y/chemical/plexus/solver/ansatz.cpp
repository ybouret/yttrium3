

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
        lK(eK.log()),
        am(_am),
        cc(_cc),
        A0(0)
        {
        }

        Ansatz:: Ansatz(const Ansatz &_) noexcept :
        eq(_.eq),
        eK(_.eK),
        lK(_.lK),
        am(_.am),
        cc(_.cc),
        A0(_.A0) 
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

        SignType Ansatz:: DecreasingAA(const Ansatz &lhs, const Ansatz &rhs) noexcept
        {
            const xreal_t laa = lhs.A0.abs();
            const xreal_t raa = rhs.A0.abs();
            return Sign::Of(raa,laa);
        }



        xreal_t Ansatz:: affinity(XAdd &xadd, const XReadable &Ctry, const Level Ltry) const
        {
            return eq.affinity(lK,xadd,Ctry,Ltry);
        }

        


    }

}
