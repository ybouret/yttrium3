
//! \file

#ifndef Y_Chemical_Plexus_Reactor_Assay_Included
#define Y_Chemical_Plexus_Reactor_Assay_Included 1

#include "y/chemical/reactive/equilibrium/aftermath.hpp"



namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! Result of 1D solution
        //
        //
        //______________________________________________________________________
        class Assay
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup from Aftermath
            Assay(const Components  &,
                  const xreal_t     &,
                  const Aftermath   &,
                  XWritable         &) noexcept;

            //! duplicate
            Assay(const Assay &) noexcept;

            //! cleanup
            ~Assay() noexcept;

            //__________________________________________________________________
            //
            //
            // Helpers
            //
            //__________________________________________________________________

            //! \return compared by decreasing am.nz then increasing am.ax
            static SignType IncreasingAX(const Assay &, const Assay &) noexcept;

            //! \return compared by decreasing |A0|
            static SignType DecreasingAA(const Assay &, const Assay &) noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \return eq affinity
            xreal_t affinity(const XReadable &, const Level, XAdd &) const;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Components & eq; //!< equilibrium
            const xreal_t      eK; //!< K for eq
            const xreal_t      lK; //!< log(K)
            const Aftermath    am; //!< 1D aftermath
            XWritable         &cc; //!< 1D solution
            const xreal_t      A0; //!< 1D initial affinity
            xreal_t            F1; //!< optimized objective function

        private:
            Y_Disable_Assign(Assay); //!< discalerd
        };

    }

}


#endif // !Y_Chemical_Plexus_Reactor_Assay_Included

