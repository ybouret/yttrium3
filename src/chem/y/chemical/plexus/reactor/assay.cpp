
#include "y/chemical/plexus/reactor/assay.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Assay:: ~Assay() noexcept
        {
        }

        Assay:: Assay(const Components  & _eq,
                      const xreal_t     & _eK,
                      const Aftermath   & _am,
                      XWritable         & _cc) noexcept :
        eq(_eq),
        eK(_eK),
        lK(eK.log()),
        am(_am),
        cc(_cc),
        A0(),
        F1()
        {
        }

        Assay:: Assay(const Assay &_) noexcept :
        eq(_.eq),
        eK(_.eK),
        lK(_.lK),
        am(_.am),
        cc(_.cc),
        A0(_.A0),
        F1(_.F1)
        {
        }

        xreal_t Assay:: affinity(const XReadable &C, const Level L, XAdd &xadd) const
        {
            return eq.affinity(lK,xadd,C,L);
        }


        SignType Assay:: IncreasingAX(const Assay &lhs, const Assay &rhs) noexcept
        {
            switch( Sign::Of(lhs.am.nz,rhs.am.nz) )
            {
                case Positive: return Negative;
                case Negative: return Positive;
                case __Zero__: break;
            }
            return Sign::Of(lhs.am.ax,rhs.am.ax);
        }

        SignType Assay:: DecreasingAA(const Assay &lhs, const Assay &rhs) noexcept
        {
            const xreal_t laa = lhs.A0.abs();
            const xreal_t raa = rhs.A0.abs();
            return Sign::Of(raa,laa);
        }


    }

}

