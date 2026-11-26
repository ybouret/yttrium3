
//! \file

#ifndef Y_MKL_Fit_SampleProbe_Included
#define Y_MKL_Fit_SampleProbe_Included 1

#include "y/mkl/fit/sample/core.hpp"
#include "y/container/matrix.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/cameo/addenda.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            template <typename ABSCISSA>
            class Probe
            {
            public:
                typedef SampleCore<ABSCISSA>                    SampleCoreType;
                typedef typename SampleCoreType::AdditionType   AdditionType;
                typedef typename SampleCoreType::AdditionHandle AdditionHandle;
                typedef Cameo::Addenda<ABSCISSA>                AddendaType;

                inline explicit Probe() :
                sumD2(), sumBeta(), sumAlpha(), addenda()
                {
                }


                inline virtual ~Probe() noexcept
                {
                }

                inline void readyFor(const size_t nvar)
                {
                    assert(nvar>0);
                    sumBeta.adjust(nvar);
                    sumAlpha.make(nvar,nvar);

                    AdditionType * node = addenda.make( (nvar*(nvar+3)) >> 1 );
                    
                    //----------------------------------------------------------
                    // fill sumBeta with nvar nodes
                    //----------------------------------------------------------
                    for(size_t i=1;i<=nvar;++i,node=node->next)
                    {
                        assert(node);
                        sumBeta[i] = node;
                    }

                    //----------------------------------------------------------
                    // fill sumAlpha with nvar*(1+nvar)/2 symetric nodes
                    //----------------------------------------------------------
                    for(size_t i=1;i<=nvar;++i)
                    {
                        for(size_t j=i;j<=nvar;++j,node=node->next)
                        {
                            assert(node);
                            sumAlpha[i][j] = sumAlpha[j][i] = node;
                        }
                    }
                    
                    sumD2.ldz();
                    addenda.ldz();
                }


                AdditionType           sumD2;
                Vector<AdditionHandle> sumBeta;
                Matrix<AdditionHandle> sumAlpha;
                AddendaType            addenda;

            private:
                Y_Disable_Copy_And_Assign(Probe);


            };
        }

    }

}


#endif // !Y_MKL_Fit_SampleProbe_Included
