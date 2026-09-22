
//! \file

#ifndef Y_Chemical_Plexus_Reactor_Included
#define Y_Chemical_Plexus_Reactor_Included 1

#include "y/chemical/plexus/cluster.hpp"
#include "y/chemical/reactive/erepo.hpp"

#include "y/chemical/reactive/equilibrium/aftermath.hpp"
#include "y/container/cxx/series.hpp"

#include "y/coven/finder.hpp"

namespace Yttrium
{
    namespace Chemical
    {


        class Resources : public Object
        {
        public:

            explicit Resources(const size_t N, const size_t M);
            virtual ~Resources() noexcept;

            AutoPtr<Coven::Finder> finder;

        private:
            Y_Disable_Copy_And_Assign(Resources);
        };

        class Assay
        {
        public:
            Assay(const Equilibrium &,
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


            const Equilibrium &eq; //!< equilibrium
            const xreal_t      eK; //!< K for eq
            const xreal_t      lK; //!< log(K)
            const Aftermath    am; //!< 1D aftermath
            XWritable         &cc; //!< 1D solution
            const xreal_t      A0; //!< 1D initial affinity

        private:
            Y_Disable_Assign(Assay);
        };

        class Reactor : public Object
        {
        public:

            enum Outcome
            {
                Improved,
                Achieved,
                Spurious
            };

            explicit Reactor(const Cluster &);
            virtual ~Reactor() noexcept;


            Outcome run(XML::Log &xml,
                        XWritable &C,
                        const Level L,
                        const XReadable &K);


            xreal_t ObjectiveFunction(const XReadable &, const Level);



            const Cluster &  cluster;
            const size_t  &  N;    //!< original number of equilibria
            const size_t  &  M;    //!< number of reactive species
            const size_t  &  n;    //!< total number of equilibria
            XArray           Cini; //!< initial   SubLevel concentrations
            XArray           Cend; //!< end point SubLevel concentrations
            XArray           Ctry; //!< trial     SubLevel concentrations
            XMatrix          Ceq;  //!< 1D solutions [n:M]
            CxxSeries<Assay> assays;
            XMul             xmul;
            XAdd             xadd;
            XAdd             fadd;

        private:
            Y_Disable_Copy_And_Assign(Reactor);
            size_t buildAssays(XML::Log &, XWritable &, const Level, const XReadable &);
            

        };

    }

}


#endif // !Y_Chemical_Plexus_Reactor_Included

