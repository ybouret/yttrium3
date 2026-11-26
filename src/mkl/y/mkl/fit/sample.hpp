//! \file

#ifndef Y_MKL_Fit_Sample_Included
#define Y_MKL_Fit_Sample_Included 1

#include "y/mkl/fit/sample/probe.hpp"
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
                typedef Probe<ABSCISSA>                   ProbeType;      //!< alias
                
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

                //! gather D2 only
                /**
                 \param probe updated
                 \param F     function
                 \param aorg  current parameters
                 */
                virtual void gatherD2(ProbeType                &probe,
                                      FunctionType             &F,
                                      const Readable<ABSCISSA> &aorg) = 0;


                //! gather D2 and differential metrics
                /**
                 \param probe    updated
                 \param G        function/gradient
                 \param aorg     current parameters
                 \param used     flags
                 \param dFda     local gradient memory
                 */
                virtual void gatherD2(ProbeType                & probe,
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

                //! compute D2 only
                /**
                 \param probe updated
                 \param F     function
                 \param aorg  current parameters
                 */
                inline ABSCISSA D2(ProbeType                &probe,
                                   FunctionType             & F,
                                   const Readable<ABSCISSA> & aorg)
                {
                    Y_Lock(access);
                    gatherD2(probe,F,aorg);
                    return probe.sumD2();
                }

                //! compute D2 and gather differential metrics
                /**
                 \param probe    updated
                 \param G        function/gradient
                 \param aorg     current parameters
                 \param used     flags
                 \param dFda     local gradient memory
                 */
                inline ABSCISSA D2(ProbeType                & probe,
                                   GradientType             & G,
                                   const Readable<ABSCISSA> & aorg,
                                   const Readable<bool>     & used,
                                   Writable<ORDINATE>       & dFda)
                {
                    Y_Lock(access);
                    gatherD2(probe,G,aorg,used,dFda);
                    return probe.sumD2();
                }

                

            private:
                Y_Disable_Copy_And_Assign(Sample); //!< dicarded

            protected:

                //! update only D2
                static inline void UpdateOnlyD2(ProbeType   &probe,
                                                const ORDINATE &y,
                                                const ORDINATE &yf)
                {
                    const ORDINATE delta = y - yf;
                    probe.sumD2 << delta*delta;
                }

                //! update D2 and all differential metrics
                inline void updateEntire(ProbeType                & probe,
                                         const Readable<ORDINATE> & dFda,
                                         const ORDINATE           & y,
                                         const ORDINATE           & yf,
                                         const Readable<bool>     & used)
                {
                    //----------------------------------------------------------
                    // compute delta
                    //----------------------------------------------------------
                    const ORDINATE delta = y - yf;

                    //std::cerr << "delta = " << delta << "; dFda  = " << dFda  << std::endl;


                    //----------------------------------------------------------
                    // store D2 component
                    //----------------------------------------------------------
                    probe.sumD2 << delta*delta;

                    //----------------------------------------------------------
                    // store other components
                    //----------------------------------------------------------
                    Variables::ConstIterator it = vars->begin();
                    for(size_t i=vars->size();i>0;--i,++it)
                    {
                        //------------------------------------------------------
                        // for beta
                        //------------------------------------------------------
                        const Variable &var_i  = **it; if(!var_i[used]) continue;
                        const ORDINATE  dFda_i = var_i[dFda];
                        *var_i[probe.sumBeta] << (dFda_i * delta);

                        //------------------------------------------------------
                        // for alpha
                        //------------------------------------------------------
                        {
                            MatrixRow<AdditionHandle> &sa_i = var_i[probe.sumAlpha];
                            Variables::ConstIterator   jt   = it;
                            for(size_t j=i;j>0;--j,++jt)
                            {
                                const Variable &var_j  = **jt; if(!var_j[used]) continue;
                                const ORDINATE  dFda_j = var_j[dFda];
                                const ABSCISSA  atmp   = dFda_i * dFda_j;
                                *var_j[sa_i] << atmp;
                            }
                        }
                    }
                }
            };

        }

    }

}



#endif // !Y_MKL_Fit_Sample_Included

