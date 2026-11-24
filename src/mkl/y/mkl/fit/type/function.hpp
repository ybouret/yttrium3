
//! \file

#ifndef Y_MKL_Fit_Function_Included
#define Y_MKL_Fit_Function_Included 1

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
            //! Function Interface
            //
            //
            //__________________________________________________________________
            template <typename ABSCISSA, typename ORDINATE>
            class Function
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                inline explicit Function() noexcept {} //!< setup
                inline virtual ~Function() noexcept {} //!< cleanup

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________

                //! initialize/get first value
                /**
                 \param x    abscissa
                 \param vars variables
                 \param aorg current parameters
                 \return initial value
                 */
                virtual ORDINATE start(const ABSCISSA &x, const Variables &vars, const Readable<ABSCISSA> &aorg) = 0;


                //! initialize/get first value
                /**
                 \param x    abscissa
                 \param vars variables
                 \param aorg current parameters
                 \return bulk value
                 */
                virtual ORDINATE value(const ABSCISSA &x, const Variables &vars, const Readable<ABSCISSA> &aorg) = 0;

            private:
                Y_Disable_Copy_And_Assign(Function); //!< discared
            };

            //__________________________________________________________________
            //
            //
            //
            //! Ordinary Function Interface
            //
            //
            //__________________________________________________________________
            template <typename ABSCISSA, typename ORDINATE>
            class OrdinaryFunction : public Function<ABSCISSA,ORDINATE>
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                inline explicit OrdinaryFunction() noexcept {} //!< setup
                inline virtual ~OrdinaryFunction() noexcept {} //!< cleanup

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                inline virtual ORDINATE start(const ABSCISSA &x, const Variables &vars, const Readable<ABSCISSA> &aorg)
                {
                    return get(x,vars,aorg);
                }

                inline virtual ORDINATE value(const ABSCISSA &x, const Variables &vars, const Readable<ABSCISSA> &aorg)
                {
                    return get(x,vars,aorg);
                }

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! any valid value evaluation
                /**
                 \param x    abscissa
                 \param vars variables
                 \param aorg current parameters
                 \return evaluated value
                 */
                inline ORDINATE operator()(const ABSCISSA x, const Variables &vars, const Readable<ABSCISSA> &aorg)
                {
                    return get(x,vars,aorg);
                }

            private:
                Y_Disable_Copy_And_Assign(OrdinaryFunction); //!< discarde

                //! specific interface \return any valid value
                virtual ORDINATE get(const ABSCISSA &, const Variables &, const Readable<ABSCISSA> &) = 0;
            };

        }

    }
}


#endif // !Y_MKL_Fit_Function_Included

