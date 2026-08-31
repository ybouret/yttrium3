//! \file

#ifndef Y_Chemical_Plexus_Ansatz_Included
#define Y_Chemical_Plexus_Ansatz_Included 1

#include "y/chemical/plexus/cluster.hpp"
#include "y/chemical/reactive/equilibrium/aftermath.hpp"
#include "y/container/cxx/series.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        //______________________________________________________________________
        //
        //
        //
        //! 1D Ansatz for the a solver
        //
        //
        //______________________________________________________________________
        class Ansatz
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef CxxSeries<Ansatz> Series; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            Ansatz(const Equilibrium &,
                   const xreal_t     &,
                   const Aftermath   &,
                   const XReadable   &) noexcept;

            //! duplicate
            Ansatz(const Ansatz &) noexcept;

            //! cleanup
            ~Ansatz() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \return sign to take the smallest |xi| that solves the biggest nz
            static  SignType IncreasingAX(const Ansatz &, const Ansatz &) noexcept;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Equilibrium & eq; //!< source equilibrium
            const xreal_t       eK; //!< source constant
            const Aftermath     am; //!< 1D aftermath
            const XReadable &   cc; //!< 1D solved concentration

        private:
            Y_Disable_Assign(Ansatz); //!< discarded
        };
    }

}

#endif // !Y_Chemical_Plexus_Ansatz_Included

