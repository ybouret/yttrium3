//! \file

#ifndef Y_MKL_Fit_Sample_Included
#define Y_MKL_Fit_Sample_Included 1

#include "y/mkl/fit/sample/core.hpp"
#include "y/mkl/fit/type/function.hpp"
#include "y/mkl/fit/type/gradient.hpp"

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
            //! Sample Interface
            //
            //
            //__________________________________________________________________
            template <typename ABSCISSA, typename ORDINATE>
            class Sample : public SampleCore<ABSCISSA>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Function<ABSCISSA,ORDINATE>       FunctionType;   //!< alias
                typedef Gradient<ABSCISSA,ORDINATE>       GradientType;   //!< alias
                typedef SampleCore<ABSCISSA>              CoreType;       //!< alias
                typedef typename CoreType::AdditionType   AdditionType;   //!< alias
                typedef typename CoreType::AdditionHandle AdditionHandle; //!< alias
                typedef Keyed<String,ArcPtr<Sample>>      Pointer;        //!< alias

                using SampleMetrics::access;
                using SampleMetrics::vars;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup with at least one AdditionType \param name compatible name
                template <typename NAME> inline
                explicit Sample(const NAME &name) :
                SampleCore<ABSCISSA>(name)
                {
                }

                //! cleanup
                inline virtual ~Sample() noexcept {}

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual void gatherD2(AdditionType             &sumD2,
                                      FunctionType             &F,
                                      const Readable<ABSCISSA> &aorg) = 0;

                virtual void gatherD2(AdditionType             & sumD2,
                                      Writable<AdditionHandle> & sumBeta,
                                      GradientType             & G,
                                      const Readable<ABSCISSA> & aorg,
                                      const Readable<bool>     & used,
                                      Writable<ORDINATE>       & dFda) = 0;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                inline ABSCISSA D2(AdditionType             & sumD2,
                                   FunctionType             & F,
                                   const Readable<ABSCISSA> & aorg)
                {
                    Y_Lock(access);
                    sumD2.ldz();
                    gatherD2(sumD2,F,aorg);
                    return sumD2();
                }

                inline ABSCISSA D2(AdditionType             & sumD2,
                                   Writable<AdditionHandle> & sumBeta,
                                   GradientType             & G,
                                   const Readable<ABSCISSA> & aorg,
                                   const Readable<bool>     & used,
                                   Writable<ORDINATE>       & dFda)
                {
                    Y_Lock(access);
                    sumD2.ldz();
                    for(size_t i=sumBeta.size();i>0;--i) sumBeta[i]->ldz();
                    gatherD2(sumD2,sumBeta,G,aorg,used,dFda);
                    return sumD2();
                }

                

            private:
                Y_Disable_Copy_And_Assign(Sample); //!< dicarded

            protected:
                static inline void UpdateOnlyD2(AdditionType &sumD2, const ORDINATE &y, const ORDINATE &yf)
                {
                    const ORDINATE delta = y - yf;
                    sumD2 << delta*delta;
                }

                inline void updateEntire(AdditionType             & sumD2,
                                         Writable<AdditionHandle> & sumBeta,
                                         const Readable<ORDINATE> & dFda,
                                         const ORDINATE           & y,
                                         const ORDINATE           & yf,
                                         const Readable<bool>     & used)
                {

                    // compute delta
                    const ORDINATE delta = y - yf;
                    //std::cerr << "dFda=" << dFda << " / delta=" << delta << std::endl;

                    // store D2 component
                    sumD2 << delta*delta;

                    // store other components
                    Variables::ConstIterator it = vars->begin();
                    for(size_t i=vars->size();i>0;--i,++it)
                    {
                        const Variable &var = **it; if(!var[used]) continue;
                        const ABSCISSA  tmp = var[dFda] * delta;
                        //std::cerr << "\tstoring " << tmp << std::endl;
                        *var[sumBeta] << tmp;
                    }
                }
            };

        }

    }

}



#endif // !Y_MKL_Fit_Sample_Included

