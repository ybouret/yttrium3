
//! \file

#ifndef Y_MKL_Fit_LeastSquaresCore_Included
#define Y_MKL_Fit_LeastSquaresCore_Included 1


#include "y/mkl/fit/sample/metrics.hpp"
#include "y/cameo/addenda.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/container/matrix.hpp"
#include "y/mkl/numeric.hpp"
#include "y/field/1d.hpp"
#include "y/pointer/auto.hpp"

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
            //! ABSCISSA only part of LeastSquares
            //
            //
            //__________________________________________________________________
            template <typename ABSCISSA>
            class LeastSquaresCore
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const unit_t PMIN;
                static const unit_t PMAX;
                typedef Cameo::Addition<ABSCISSA> AdditionType;   //!< alias
                typedef Cameo::Addenda<ABSCISSA>  AddendaType;    //!< alias
                typedef AdditionType *            AdditionHandle; //!< alias
                typedef Field::In1D<ABSCISSA>     Lambda;         //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                inline explicit LeastSquaresCore() :
                sumD2(),
                last(-1),
                beta(),
                alpha(),
                sumBeta(),
                sumAlpha(),
                addenda(),
                lambda( "lambda", Field::Layout1D(PMIN,PMAX) ),
                zero(0),
                one(1)
                {
                    buildLambda();

                }

                inline virtual ~LeastSquaresCore() noexcept
                {
                }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                AdditionType             sumD2;    //!< sum of D2
                ABSCISSA                 last;     //!< last D2
                Vector<ABSCISSA>         beta;     //!< descent direction
                Matrix<ABSCISSA>         alpha;    //!< approximate hessian
                Vector<AdditionHandle>   sumBeta;  //!< helper to compute beta
                Matrix<AdditionHandle>   sumAlpha; //!< helper to compute alpha
                AddendaType              addenda;  //!< dynamic inner additions
                const Lambda             lambda;   //!< inner lambda values
                const ABSCISSA           zero;     //!< 0
                const ABSCISSA           one;      //!< 1

            private:
                Y_Disable_Copy_And_Assign(LeastSquaresCore); //!< discarded

            protected:
                inline void buildLambda()
                {
                    const ABSCISSA ten = 10;
                    Coerce(lambda[0]) = 1;
                    for(unit_t i=-1;i>PMIN;--i) Coerce(lambda[i]) = lambda[i+1]/ten;
                    for(unit_t i=1;i<=PMAX;++i) Coerce(lambda[i]) = lambda[i-1]*ten;
                    //Core::Display(std::cerr, &lambda[PMIN], lambda->width) << std::endl;
                }

                //! prepare core memory \param nvar number of variables
                inline void prepareCoreFor(const size_t nvar)
                {
                    //----------------------------------------------------------
                    // prepare beta
                    //----------------------------------------------------------
                    beta.adjust(nvar);
                    beta.ld(zero);

                    //----------------------------------------------------------
                    // prepare alpha
                    //----------------------------------------------------------
                    alpha.make(nvar,nvar);
                    alpha.ld(zero).diag(one);

                    //----------------------------------------------------------
                    // prepare addition handles
                    //----------------------------------------------------------
                    sumBeta.adjust(nvar);
                    sumAlpha.make(nvar,nvar);

                    //----------------------------------------------------------
                    // prepare addenda
                    //----------------------------------------------------------
                    AdditionType * node = addenda.make( SampleMetrics::AddendaSizeFor(nvar) );

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
                }

                //! compile beta and alpha from sumBeta and sumAlpha
                /**
                 \param vars variables
                 \param used flags
                 */
                inline void compileFrom(const Variables      &vars,
                                        const Readable<bool> &used)
                {
                    Variables::ConstIterator it = vars->begin();
                    for(size_t i=vars->size();i>0;--i,++it)
                    {
                        const Variable &v_i = **it;if(!v_i[used]) continue;
                        AdditionType   &sum = *v_i[sumBeta];
                        v_i[beta] = sum();

                        MatrixRow<AdditionHandle> &sa_i = v_i[sumAlpha];
                        MatrixRow<ABSCISSA>       &a_i  = v_i[alpha];
                        Variables::ConstIterator   jt   = it;
                        for(size_t j=i;j>0;--j,++jt)
                        {
                            const Variable &v_j = **jt; if(!v_j[used]) continue;
                            AdditionType   &sum = *v_j[sa_i];
                            const ABSCISSA  a_ij = sum();
                            v_j[a_i]        = a_ij;
                            v_i[v_j[alpha]] = a_ij;
                        }

                    }
                }

            };

            template <typename ABSCISSA>
            const unit_t LeastSquaresCore<ABSCISSA>::PMIN = - (int)( Numeric<ABSCISSA>::DIG + 1);

            template <typename ABSCISSA>
            const unit_t LeastSquaresCore<ABSCISSA>::PMAX = Numeric<ABSCISSA>::MAX_10_EXP;


        }
    }
}

#endif // !Y_MKL_Fit_LeastSquaresCore_Included

