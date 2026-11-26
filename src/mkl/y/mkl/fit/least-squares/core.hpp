
//! \file

#ifndef Y_MKL_Fit_LeastSquaresCore_Included
#define Y_MKL_Fit_LeastSquaresCore_Included 1


#include "y/mkl/fit/sample/probe.hpp"
#include "y/mkl/numeric.hpp"
#include "y/field/1d.hpp"
#include "y/pointer/auto.hpp"
#include "y/mkl/algebra/lu.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            enum CurvatureResult
            {
                Straight, //!< used required lambda
                Expanded, //!< needed expansion
                Singular  //!< too much expansion
            };

            //__________________________________________________________________
            //
            //
            //
            //! ABSCISSA only part of LeastSquares
            //
            //
            //__________________________________________________________________
            template <typename ABSCISSA>
            class LeastSquaresCore : public Probe<ABSCISSA>
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
                typedef Field::In1D<ABSCISSA>              Lambda;         //!< alias
                typedef Probe<ABSCISSA>                    ProbeType;
                typedef typename ProbeType::AdditionHandle AdditionHandle;
                typedef typename ProbeType::AdditionType   AdditionType;

                using ProbeType::sumBeta;
                using ProbeType::sumAlpha;




                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                inline explicit LeastSquaresCore() :
                beta(),
                alpha(),
                curv(),
                lu(),
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
                Vector<ABSCISSA>         beta;     //!< descent direction
                Matrix<ABSCISSA>         alpha;    //!< approximate hessian
                Matrix<ABSCISSA>         curv;     //!< approximate curvature
                LU<ABSCISSA>             lu;       //!< linear algebra
                Vector<ABSCISSA>         atry;     //!< trial parameters
                const Lambda             lambda;   //!< inner lambda values
                const ABSCISSA           zero;     //!< 0
                const ABSCISSA           one;      //!< 1

            private:
                Y_Disable_Copy_And_Assign(LeastSquaresCore); //!< discarded

            protected:

                //! building lambda field
                inline void buildLambda()
                {
                    const ABSCISSA ten = 10;
                    Coerce(lambda[0]) = 1;
                    for(unit_t i=-1;i>PMIN;--i) Coerce(lambda[i]) = lambda[i+1]/ten;
                    for(unit_t i=1;i<=PMAX;++i) Coerce(lambda[i]) = lambda[i-1]*ten;
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
                    // prepare alpha and curv
                    //----------------------------------------------------------
                    alpha.make(nvar,nvar);
                    alpha.ld(zero).diag(one);
                    curv.make(nvar,nvar);

                    //----------------------------------------------------------
                    // prepare other
                    //----------------------------------------------------------
                    atry.adjust(nvar);

                    //----------------------------------------------------------
                    // prepare inner additions
                    //----------------------------------------------------------
                    this->readyFor(nvar);
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


                inline CurvatureResult buildCurvature(unit_t &p)
                {
                    assert(p>=PMIN);
                    assert(p<=PMAX);
                    size_t         cycle = 1;
                SCALE:
                    const ABSCISSA scale = one; //+ lambda[p];
                    curv.assign(alpha);
                    for(size_t i=curv.rows;i>0;--i)
                        curv[i][i] *= scale;

                    
                    if( lu.build(curv) )
                        return (1 == cycle) ? Straight : Expanded;

                    if(++p>PMAX) return Singular;
                    ++cycle;
                    goto SCALE;
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

