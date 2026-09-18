
//! \file

#ifndef Y_Chemical_Plexus_Algebra_Included
#define Y_Chemical_Plexus_Algebra_Included 1

#include "y/chemical/type/defs.hpp"
#include "y/chemical/type/matrix.hpp"
#include "y/container/cxx/series.hpp"
#include "y/mkl/algebra/lu.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! Algebraic Content to compute effective step
        //
        //
        //______________________________________________________________________
        class Algebra : public Object
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Algebra(const size_t n, const size_t m); //!< setup \param n initial equilibria \param m sublevel species
            virtual ~Algebra() noexcept;                      //!< cleanup

            //__________________________________________________________________
            //
            //
            //  Members
            //
            //__________________________________________________________________
            MKL::LU<xreal_t>   lu;  //!< linear solver
            CxxSeries<XMatrix> J;   //!< xi/Jacobians matrices
            CxxSeries<XMatrix> dA;  //!< Affinity Jacobians
            CxxSeries<XMatrix> nu;  //!< local topologies
            CxxSeries<XMatrix> nuT; //!< local tranpose topologies
            CxxSeries<XArray>  xi;  //!< local extents

        private:
            Y_Disable_Copy_And_Assign(Algebra); //!< discarded
        };
    }

}

#endif // !Y_Chemical_Plexus_Algebra_Included

