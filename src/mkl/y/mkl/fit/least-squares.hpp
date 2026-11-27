//! \file

#ifndef Y_MKL_Fit_LeastSquares_Included
#define Y_MKL_Fit_LeastSquares_Included 1


#include "y/mkl/fit/least-squares/core.hpp"
#include "y/mkl/fit/sample.hpp"
#include "y/type/temporary.hpp"
#include "y/stream/libc/output.hpp"
#include "y/core/secure.hpp"
#include "y/xml/element.hpp"

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
            //! LeastSquares interface
            //
            //
            //__________________________________________________________________
            template <typename ABSCISSA, typename ORDINATE>
            class LeastSquares : public LeastSquaresCore<ABSCISSA>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef LeastSquaresCore<ABSCISSA>          CoreType;       //!< alias
                typedef typename CoreType::AddendaType      AddendaType;    //!< alias
                typedef Sample<ABSCISSA,ORDINATE>           SampleType;     //!< alias
                typedef typename SampleType::FunctionType   FunctionType;   //!< alias
                typedef typename SampleType::GradientType   GradientType;   //!< alias
                typedef typename SampleType::AdditionType   AdditionType;   //!< alias
                typedef typename SampleType::AdditionHandle AdditionHandle; //!< alias

                using CoreType:: beta;
                using CoreType:: curv;
                using CoreType:: step;
                using CoreType:: aini;
                using CoreType:: aend;
                using CoreType:: atmp;

                using CoreType:: one;
                using CoreType:: zero;

                using CoreType:: sumD2;
                using CoreType:: sumBeta;
                using CoreType:: sumAlpha;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                inline explicit LeastSquares()  :
                CoreType(),
                dFda(),
                myF(0),
                myS(0)
                {

                }

                inline virtual ~LeastSquares() noexcept
                {

                }

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! compute D2
                /**
                 \param S sample
                 \param F function
                 \param a parameters
                 \return current D2
                 */
                inline ABSCISSA D2(SampleType               &S,
                                   FunctionType             &F,
                                   const Readable<ABSCISSA> &a)
                {
                    sumD2.ldz();
                    return S.D2(*this,F,a);
                }

                //! compute D2 and differential metrics
                /**
                 \param S    sample
                 \param G    gradient
                 \param aorg parameters
                 \param used flags
                 \return current D2
                 */
                inline ABSCISSA D2full(SampleType               &S,
                                       GradientType             &G,
                                       const Readable<ABSCISSA> &aorg,
                                       const Readable<bool>     &used)
                {
                    //----------------------------------------------------------
                    // prepare resources
                    //----------------------------------------------------------
                    prepareFor(S);

                    //----------------------------------------------------------
                    // gather components
                    //----------------------------------------------------------
                    const ABSCISSA result =  S.D2(*this,G,aorg,used,dFda);

                    //----------------------------------------------------------
                    // compile components
                    //----------------------------------------------------------
                    this->compileFrom(S.vars,used);

                    //----------------------------------------------------------
                    // return D2
                    //----------------------------------------------------------
                    return result;
                }

#include "y/mkl/fit/least-squares/loop.hxx"

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                Vector<ORDINATE> dFda; //!< local gradient


            private:
                Y_Disable_Copy_And_Assign(LeastSquares); //!< discarded
                FunctionType * myF;
                SampleType   * myS;

                //! prepare all memory
                inline void prepareFor(const SampleType &S)
                {
                    const size_t nvar = S.vars.span;
                    this->prepareCoreFor(nvar);
                    dFda.adjust(nvar);
                }

                inline virtual ABSCISSA operator()(const ABSCISSA u)
                {
                    assert(myF);
                    FunctionType  &F = *myF;
                    const ABSCISSA v = one-u;
                    const size_t   n = aini.size();
                    for(size_t i=n;i>0;--i)
                    {
                        const ABSCISSA a0 = aini[i], a1 = aend[i];
                        atmp[i] = Secure<ABSCISSA>(a0,v*a0 + u*a1,a1);
                    }
                    return D2(*myS,F,atmp);
                }
            };

        }

    }
}



#endif // !Y_MKL_Fit_LeastSquares_Included
