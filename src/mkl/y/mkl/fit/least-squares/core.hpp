
//! \file

#ifndef Y_MKL_Fit_LeastSquaresCore_Included
#define Y_MKL_Fit_LeastSquaresCore_Included 1


#include "y/mkl/fit/sample/metrics.hpp"
#include "y/cameo/addenda.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/container/matrix.hpp"

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
                typedef Cameo::Addition<ABSCISSA> AdditionType;
                typedef Cameo::Addenda<ABSCISSA>  AddendaType;
                typedef AdditionType *            AdditionHandle;

                inline explicit LeastSquaresCore() :
                sumD2(),
                last(-1),
                beta(),
                sumBeta(),
                sumAlpha(),
                addenda(),
                zero(0),
                one(1)
                {
                }

                inline virtual ~LeastSquaresCore() noexcept
                {
                }


                AdditionType             sumD2;
                ABSCISSA                 last;
                Vector<ABSCISSA>         beta;
                Matrix<ABSCISSA>         alpha;
                Vector<AdditionHandle>   sumBeta;
                Matrix<AdditionHandle>   sumAlpha;
                AddendaType              addenda;
                const ABSCISSA           zero;
                const ABSCISSA           one;

            private:
                Y_Disable_Copy_And_Assign(LeastSquaresCore);

            protected:

                inline void prepareCoreFor(const size_t nvar)
                {
                    // prepare beta
                    beta.adjust(nvar);
                    beta.ld(zero);

                    // prepare alpha
                    alpha.make(nvar,nvar);
                    alpha.ld(zero).diag(one);

                    sumBeta.adjust(nvar);
                    sumAlpha.make(nvar,nvar);

                    // prepare addenda
                    AdditionType * node = addenda.make( SampleMetrics::AddendaSizeFor(nvar) );

                    // fill sumBeta with nvar nodes
                    for(size_t i=1;i<=nvar;++i,node=node->next)
                    {
                        assert(node);
                        sumBeta[i] = node;
                    }

                    // fill sumAlpha with nvar*(1+nvar)/2 symetric nodes
                    for(size_t i=1;i<=nvar;++i)
                    {
                        for(size_t j=i;j<=nvar;++j,node=node->next)
                        {
                            assert(node);
                            sumAlpha[i][j] = sumAlpha[j][i] = node;
                        }
                    }
                }

                inline void compileFrom(const Variables      &vars,
                                        const Readable<bool> &used)
                {
                    Variables::ConstIterator it = vars->begin();
                    for(size_t i=vars->size();i>0;--i,++it)
                    {
                        const Variable &var = **it;if(!var[used]) continue;
                        AdditionType   &sum = *var[sumBeta];
                        var[beta] = sum();
                    }
                }

            };

        }
    }
}

#endif // !Y_MKL_Fit_LeastSquaresCore_Included

