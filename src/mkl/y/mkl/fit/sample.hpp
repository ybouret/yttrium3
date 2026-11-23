//! \file

#ifndef Y_MKL_Fit_Sample_Included
#define Y_MKL_Fit_Sample_Included 1

#include "y/mkl/fit/sample/metrics.hpp"
#include "y/mkl/fit/type/function.hpp"
#include "y/cameo/addition.hpp"
#include "y/mkl/api/mod2.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            template <typename ABSCISSA, typename ORDINATE>
            class Sample : public SampleMetrics
            {
            public:
                typedef Function<ABSCISSA,ORDINATE>  FunctionType;
                typedef Cameo::Addition<ABSCISSA>    AdditionType;
                typedef Keyed<String,ArcPtr<Sample>> Pointer;

                template <typename NAME> inline
                explicit Sample(const NAME &name) :
                SampleMetrics(name),
                xadd()
                {

                }

                inline virtual ~Sample() noexcept {}


                virtual void collectD2(AdditionType             &sumD2,
                                       FunctionType             &F,
                                       const Readable<ABSCISSA> &aorg) = 0;


                inline ABSCISSA D2(FunctionType &F, const Readable<ABSCISSA> &aorg)
                {
                    xadd.ldz();
                    collectD2(xadd,F,aorg);
                    return xadd();
                }

                AdditionType xadd;

            private:
                Y_Disable_Copy_And_Assign(Sample);

            protected:
                inline ABSCISSA collect(const ORDINATE &lhs, const ORDINATE &rhs)
                {
                    const ORDINATE delta = lhs-rhs;
                    return Mod2<ORDINATE>(delta);
                }
            };

        }

    }

}



#endif // !Y_MKL_Fit_Sample_Included

