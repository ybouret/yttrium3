
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
            explicit Algebra(const size_t n, const size_t m); //!< setup \param n initial equilibria \param m sublevel species
            virtual ~Algebra() noexcept;                      //!< cleanup

            MKL::LU<xreal_t>   lu;
            CxxSeries<XMatrix> J;
            CxxSeries<XMatrix> dA;
            CxxSeries<XMatrix> nu;
            CxxSeries<XMatrix> nuT;
            CxxSeries<XArray>  xi;
            
        private:
            Y_Disable_Copy_And_Assign(Algebra);
        };
    }

}

#endif // !Y_Chemical_Plexus_Algebra_Included

