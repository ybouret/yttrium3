
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

            //__________________________________________________________________
            //
            //
            //! Curvature computation result
            //
            //__________________________________________________________________
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
                static const unit_t PMIN; //!< minimum approximation lambda[PMIN] = 0
                static const unit_t PMAX; //!< maximum approximation
                typedef Field::In1D<ABSCISSA>              Lambda;         //!< alias
                typedef Probe<ABSCISSA>                    ProbeType;      //!< alias
                typedef typename ProbeType::AdditionHandle AdditionHandle; //!< alias
                typedef typename ProbeType::AdditionType   AdditionType;   //!< alias

                using ProbeType::sumBeta;
                using ProbeType::sumAlpha;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit LeastSquaresCore();          //!< setup
                virtual ~LeastSquaresCore() noexcept; //!< cleanup

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
                Vector<ABSCISSA>         aini;     //!< ini point
                Vector<ABSCISSA>         aend;     //!< end point]
                Vector<ABSCISSA>         atmp;     //!< tmp point
                const Lambda             lambda;   //!< inner lambda values
                const ABSCISSA           zero;     //!< 0
                const ABSCISSA           one;      //!< 1

            private:
                Y_Disable_Copy_And_Assign(LeastSquaresCore); //!< discarded

            protected:
                virtual ABSCISSA operator()(const ABSCISSA) = 0;

                void buildLambda() noexcept; //!< setup lamnda

                //! prepare core memory \param nvar number of variables
                void prepareCoreFor(const size_t nvar);


                //! compile beta and alpha from sumBeta and sumAlpha
                /**
                 \param vars variables
                 \param used flags
                 */
                void compileFrom(const Variables      &vars,
                                 const Readable<bool> &used);


                //! compile curvature from alpha and lambda[p]
                /**
                 \param  p approximation
                 \return Straight: ok, Expanded: p was increased, Singular: singular point
                 */
                CurvatureResult buildCurvature(unit_t &p);


            };

            //! definition
            template <typename ABSCISSA>
            const unit_t LeastSquaresCore<ABSCISSA>::PMIN = - (int)( Numeric<ABSCISSA>::DIG + 1);

            //! defintion
            template <typename ABSCISSA>
            const unit_t LeastSquaresCore<ABSCISSA>::PMAX = Numeric<ABSCISSA>::MAX_10_EXP;


        }
    }
}

#endif // !Y_MKL_Fit_LeastSquaresCore_Included

