
//! \file

#ifndef Y_MKL_Fit_Gradient_Included
#define Y_MKL_Fit_Gradient_Included 1

#include "y/mkl/fit/variables.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            template <typename ABSCISSA, typename ORDINATE>
            class Gradient
            {
            public:

                inline explicit Gradient() noexcept {}
                inline virtual ~Gradient() noexcept {}

                virtual ORDINATE start(Writable<ORDINATE> &dFda, const ABSCISSA &x, const Variables &vars, const Readable<ABSCISSA> &aorg, const Readable<bool> &used) = 0;
                virtual ORDINATE value(Writable<ORDINATE> &dFda, const ABSCISSA &x, const Variables &vars, const Readable<ABSCISSA> &aorg, const Readable<bool> &used) = 0;

            private:
                Y_Disable_Copy_And_Assign(Gradient);
            };

        }

    }

}

#endif // !Y_MKL_Fit_Gradient_Included

