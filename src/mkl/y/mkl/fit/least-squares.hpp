//! \file

#ifndef Y_MKL_Fit_LeastSquares_Included
#define Y_MKL_Fit_LeastSquares_Included 1

#include "y/mkl/fit/sample.hpp"
#include "y/cameo/addenda.hpp"
#include "y/container/sequence/vector.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            template <typename ABSCISSA, typename ORDINATE>
            class LeastSquares
            {
            public:
                typedef Sample<ABSCISSA,ORDINATE>         SampleType;
                typedef typename SampleType::FunctionType FunctionType;
                typedef typename SampleType::AdditionType AdditionType;
                typedef typename SampleType::AdditionHandle AdditionHandle;

                inline explicit LeastSquares()  :
                sumD2()
                {

                }

                inline virtual ~LeastSquares() noexcept
                {

                }

                inline ABSCISSA D2(SampleType               &S,
                                   FunctionType             &F,
                                   const Readable<ABSCISSA> &a)
                {
                    return S.D2(sumD2,F,a);
                }



                AdditionType             sumD2;
                Vector<AdditionHandle>   sumBeta;
                Cameo::Addenda<ABSCISSA> addenda;


            private:
                Y_Disable_Copy_And_Assign(LeastSquares);
            };

        }

    }
}



#endif // !Y_MKL_Fit_LeastSquares_Included
