
//! \file

#ifndef Y_MKL_Fit_LeastSquaresCore_Included
#define Y_MKL_Fit_LeastSquaresCore_Included 1


#include "y/mkl/fit/sample/metrics.hpp"
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
                typedef Cameo::Addition<ABSCISSA> AdditionType;
                typedef Cameo::Addenda<ABSCISSA>  AddendaType;
                typedef AdditionType *            AdditionHandle;

                inline explicit LeastSquaresCore() :
                sumD2(),
                last(-1),
                beta(),
                sumBeta(),
                addenda(),
                zero(0)
                {
                }

                inline virtual ~LeastSquaresCore() noexcept
                {
                }


                AdditionType             sumD2;
                ABSCISSA                 last;
                Vector<ABSCISSA>         beta;
                Vector<AdditionHandle>   sumBeta;
                AddendaType              addenda;
                const ABSCISSA           zero;

            private:
                Y_Disable_Copy_And_Assign(LeastSquaresCore);

            protected:
                inline void prepareCoreFor(const size_t nvar)
                {
                    beta.adjust(nvar); beta.ld(zero);
                    sumBeta.adjust(nvar);
                    AdditionType * node = addenda.make( SampleMetrics::AddendaSizeFor(nvar) );
                    for(size_t i=1;i<=nvar;++i,node=node->next)
                    {
                        assert(node);
                        sumBeta[i] = node;
                    }
                }

            };

        }
    }
}

#endif // !Y_MKL_Fit_LeastSquaresCore_Included

