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

            template <typename ABSCISSA>
            class LeastSquaresCore
            {
            public:

            private:
                Y_Disable_Copy_And_Assign(LeastSquaresCore);
            };


            template <typename ABSCISSA, typename ORDINATE>
            class LeastSquares
            {
            public:
                typedef Sample<ABSCISSA,ORDINATE>           SampleType;
                typedef typename SampleType::FunctionType   FunctionType;
                typedef typename SampleType::GradientType   GradientType;
                typedef typename SampleType::AdditionType   AdditionType;
                typedef typename SampleType::AdditionHandle AdditionHandle;

                inline explicit LeastSquares()  :
                sumD2(),
                last(-1),
                beta(),
                dFda(),
                sumBeta(),
                addenda(),
                zero(0)
                {

                }

                inline virtual ~LeastSquares() noexcept
                {

                }

                inline ABSCISSA D2(SampleType               &S,
                                   FunctionType             &F,
                                   const Readable<ABSCISSA> &a)
                {
                    return (last=S.D2(sumD2,F,a));
                }

                inline ABSCISSA D2full(SampleType               &S,
                                       GradientType             &G,
                                       const Readable<ABSCISSA> &aorg,
                                       const Readable<bool>     &used)
                {
                    prepareFor(S);
                    const ABSCISSA result = (last=S.D2(sumD2,sumBeta,G,aorg,used,dFda));

                    return result;
                }

                inline void prepareFor(const SampleType &S)
                {
                    const size_t nvar = S.vars->size();

                    beta.adjust(nvar); beta.ld(zero);
                    dFda.adjust(nvar);
                    sumBeta.adjust(nvar);
                    AdditionType * node = addenda.make( SampleType::AddendaSizeFor(nvar) );
                    for(size_t i=1;i<=nvar;++i,node=node->next)
                    {
                        assert(node);
                        sumBeta[i] = node;
                    }
                }





                AdditionType             sumD2;
                ABSCISSA                 last;
                Vector<ABSCISSA>         beta;
                Vector<ORDINATE>         dFda;
                Vector<AdditionHandle>   sumBeta;
                Cameo::Addenda<ABSCISSA> addenda;
                const ABSCISSA           zero;

            private:
                Y_Disable_Copy_And_Assign(LeastSquares);
            };

        }

    }
}



#endif // !Y_MKL_Fit_LeastSquares_Included
