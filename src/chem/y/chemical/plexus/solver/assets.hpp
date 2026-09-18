
//! \file

#ifndef Y_Chemical_Plexus_Assets_Included
#define Y_Chemical_Plexus_Assets_Included 1

#include "y/chemical/plexus/solver/algebra.hpp"
#include "y/coven/finder.hpp"
#include "y/mkl/minimize/api.hpp"
#include "y/pointer/auto.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! Assets for Solver computations
        //
        //
        //______________________________________________________________________
        class Assets : public Object
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param n initial equilibria \param m sublevel species
            explicit Assets(const size_t n, const size_t m);

            //! cleanup
            virtual ~Assets() noexcept;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________

            MKL::Minimize::Engine<xreal_t> minimize; //!< minimizer
            AutoPtr<Algebra>               algebra;  //!< algebra components
            AutoPtr<Coven::Finder>         finder;   //!< find orthogonal basis

        private:
            Y_Disable_Copy_And_Assign(Assets); //!< discarded
        };

    }

}

#endif // !Y_Chemical_Plexus_Assets_Included

