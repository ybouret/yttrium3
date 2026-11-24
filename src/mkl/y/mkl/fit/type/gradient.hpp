
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

            //__________________________________________________________________
            //
            //
            //
            //! Gradient interface
            //
            //
            //__________________________________________________________________
            template <typename ABSCISSA, typename ORDINATE>
            class Gradient
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                inline explicit Gradient() noexcept {} //!< setup
                inline virtual ~Gradient() noexcept {} //!< cleanup

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________

                //! initialize/get value and gradient at starting point
                /**
                 \param dFda output gradient
                 \param x    abscissa
                 \param vars variables
                 \param aorg parameters
                 \param used used variables
                 \return initial value/gradient
                 */
                virtual ORDINATE start(Writable<ORDINATE> &dFda, const ABSCISSA &x, const Variables &vars, const Readable<ABSCISSA> &aorg, const Readable<bool> &used) = 0;


                //! get any valid value and gradient
                /**
                 \param dFda output gradient
                 \param x    abscissa
                 \param vars variables
                 \param aorg parameters
                 \param used used variables
                 \return bulk value/gradient
                 */
                virtual ORDINATE value(Writable<ORDINATE> &dFda, const ABSCISSA &x, const Variables &vars, const Readable<ABSCISSA> &aorg, const Readable<bool> &used) = 0;

            private:
                Y_Disable_Copy_And_Assign(Gradient); //!< discarded
            };

        }

    }

}

#endif // !Y_MKL_Fit_Gradient_Included

