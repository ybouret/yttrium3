
//! \file

#ifndef Y_MKL_Fit_SampleCore_Included
#define Y_MKL_Fit_SampleCore_Included 1

#include "y/mkl/fit/sample/metrics.hpp"
#include "y/cameo/addition.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            template <typename ABSCISSA>
            class SampleCore : public SampleMetrics
            {
            public:
                typedef Cameo::Addition<ABSCISSA>    AdditionType; //!< alias
                typedef AdditionType *               AdditionHandle; //!< alias

                template <typename NAME> inline
                explicit SampleCore(const NAME &name) :
                SampleMetrics(name)
                {
                }

                inline virtual ~SampleCore() noexcept {}



            private:
                Y_Disable_Copy_And_Assign(SampleCore);
            };

        }

    }

}

#endif // !Y_MKL_Fit_SampleCore_Included

