
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

            template <typename ABSCISSA, typename ORDINATE>
            class Function
            {
            public:

                inline explicit Function() noexcept {}
                inline virtual ~Function() noexcept {}

                virtual ORDINATE start(const ABSCISSA &x, const Variables &vars, const Readable<ABSCISSA> &aorg) = 0;
                virtual ORDINATE value(const ABSCISSA &x, const Variables &vars, const Readable<ABSCISSA> &aorg) = 0;

            private:
                Y_Disable_Copy_And_Assign(Function);
            };

            template <typename ABSCISSA, typename ORDINATE>
            class OrdinaryFunction : public Function<ABSCISSA,ORDINATE>
            {
            public:

                inline explicit OrdinaryFunction() noexcept {}
                inline virtual ~OrdinaryFunction() noexcept {}

                inline virtual ORDINATE start(const ABSCISSA &x, const Variables &vars, const Readable<ABSCISSA> &aorg)
                {
                    return get(x,vars,aorg);
                }

                inline virtual ORDINATE value(const ABSCISSA &x, const Variables &vars, const Readable<ABSCISSA> &aorg)
                {
                    return get(x,vars,aorg);
                }

                inline ORDINATE operator()(const ABSCISSA x, const Variables &vars, const Readable<ABSCISSA> &aorg)
                {
                    return get(x,vars,aorg);
                }

            private:
                Y_Disable_Copy_And_Assign(OrdinaryFunction);
                virtual ORDINATE get(const ABSCISSA &, const Variables &, const Readable<ABSCISSA> &) = 0;
            };

        }

    }
}


#endif // !Y_MKL_Fit_Function_Included

