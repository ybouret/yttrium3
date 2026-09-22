
//! \file

#ifndef Y_Chemical_Plexus_Reactor_Assay_Included
#define Y_Chemical_Plexus_Reactor_Assay_Included 1

#include "y/chemical/reactive/equilibrium/aftermath.hpp"



namespace Yttrium
{
    namespace Chemical
    {
        class Assay
        {
        public:
            Assay(const Components  &,
                  const xreal_t     &,
                  const Aftermath   &,
                  XWritable         &) noexcept;

            Assay(const Assay &) noexcept;

            ~Assay() noexcept;

            static SignType IncreasingAX(const Assay &lhs, const Assay &rhs) noexcept
            {
                switch( Sign::Of(lhs.am.nz,rhs.am.nz) )
                {
                    case Positive: return Negative;
                    case Negative: return Positive;
                    case __Zero__: break;
                }
                return Sign::Of(lhs.am.ax,rhs.am.ax);
            }

            static SignType DecreasingAA(const Assay &lhs, const Assay &rhs) noexcept
            {
                const xreal_t laa = lhs.A0.abs();
                const xreal_t raa = rhs.A0.abs();
                return Sign::Of(raa,laa);
            }

            xreal_t affinity(const XReadable &, const Level, XAdd &) const;


            const Components & eq; //!< equilibrium
            const xreal_t      eK; //!< K for eq
            const xreal_t      lK; //!< log(K)
            const Aftermath    am; //!< 1D aftermath
            XWritable         &cc; //!< 1D solution
            const xreal_t      A0; //!< 1D initial affinity
            xreal_t            F1; //!< optimized objective function

        private:
            Y_Disable_Assign(Assay);
        };

    }

}


#endif // !Y_Chemical_Plexus_Reactor_Assay_Included

