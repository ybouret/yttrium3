//! \file

#ifndef Y_MKL_Fit_Sample_Included
#define Y_MKL_Fit_Sample_Included 1

#include "y/mkl/fit/sample/metrics.hpp"
#include "y/mkl/fit/type/function.hpp"
#include "y/mkl/fit/type/gradient.hpp"
#include "y/cameo/addenda.hpp"
#include "y/container/sequence/vector.hpp"

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
            class Sample : public SampleMetrics
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Function<ABSCISSA,ORDINATE>  FunctionType; //!< alias
                typedef Gradient<ABSCISSA,ORDINATE>  GradientType; //!< alias
                typedef Cameo::Addition<ABSCISSA>    AdditionType; //!< alias
                typedef Cameo::Addenda<ABSCISSA>     AddendaType;  //!< alias
                typedef Keyed<String,ArcPtr<Sample>> Pointer;      //!< alias
                typedef AdditionType *               AddHandle;    //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup with at least one AdditionType \param name compatible name
                template <typename NAME> inline
                explicit Sample(const NAME &name) :
                SampleMetrics(name),
                dsqrAdd(0),
                betaAdd(),
                addenda(),
                zero(0)
                {
                    (void) addenda.make(1);
                }

                //! cleanup
                inline virtual ~Sample() noexcept {}


                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________

                //! collect D2 contribution
                /**
                 \param sumD2 target addition
                 \param F     fit function
                 \param atry  current parameters
                 */
                virtual void collectD2(AdditionType             &sumD2,
                                       FunctionType             &F,
                                       const Readable<ABSCISSA> &atry) = 0;



                virtual void collectD2org(Writable<ORDINATE>       & dFda,
                                          AdditionType             & sumD2,
                                          Writable<AddHandle>      & sumBeta,
                                          GradientType             & G,
                                          const Readable<ABSCISSA> & aorg,
                                          const Readable<bool>     & used) = 0;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! compute local D2
                /**
                 \param  F fit function
                 \param  atry trial parameters
                 \return collected D2
                 */
                inline ABSCISSA D2(FunctionType &F, const Readable<ABSCISSA> &atry)
                {
                    AdditionType &xadd = *addenda.make(1);
                    xadd.ldz();
                    collectD2(xadd,F,atry);
                    return xadd();
                }

                inline void prepareFor(const size_t nvar)
                {
                    AddHandle handle = addenda.make( AdditionTypeCount(nvar) );
                    addenda.ldz();
                    gradient.adjust(nvar);
                    betaAdd.adjust(nvar);
                    Coerce(dsqrAdd) = handle; assert(handle);
                    for(size_t i=1;i<=nvar;++i)
                    {
                        handle=handle->next; assert(handle);
                        betaAdd[i] = handle;
                    }

                }

                inline ABSCISSA D2org(Writable<ABSCISSA>       &beta,
                                      GradientType             &G,
                                      const Readable<ABSCISSA> &aorg,
                                      const Readable<bool>     &used)
                {
                    // prepare resources
                    assert(beta.size()>=vars.span);
                    beta.ld(zero);
                    prepareFor(vars.span);

                    // collect info
                    collectD2org(gradient,*dsqrAdd,betaAdd,G,aorg,used);

                    // compile collected info
                    return compile(beta,used);
                }



                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                Vector<ORDINATE>     gradient; //!< local gradient
                AdditionType * const dsqrAdd;  //!< to add D2
                Vector<AddHandle>    betaAdd;  //!< to add beta
                AddendaType          addenda;  //!< addition helper
                const ABSCISSA       zero;     //!< 0

            private:
                Y_Disable_Copy_And_Assign(Sample); //!< dicarded

            protected:
                //! helper for squared module
                /**
                 \param y  source ordinate
                 \param yf guess ordinate
                 \return |y-yf|^2 as abscissa
                 */
                inline ABSCISSA localD2(const ORDINATE &y, const ORDINATE &yf)
                {
                    const ORDINATE delta = y-yf;
                    return delta*delta;
                }

                inline void localD2(const Readable<ORDINATE> &dFda,
                                    AdditionType             &sumD2,
                                    Writable<AddHandle>      &sumBeta,
                                    const ORDINATE           &y,
                                    const ORDINATE           &yf,
                                    const Readable<bool>     &used)
                {
                    const ORDINATE delta = y-yf;
                    sumD2 << delta*delta; // store for D2
                    Variables::ConstIterator it = vars->begin();
                    for(size_t i=vars->size();i>0;--i,++it)
                    {
                        const Variable &var = **it; if(!var[used]) continue;
                        *var[sumBeta] << var[dFda] * delta; // store for beta
                    }

                }


                inline ABSCISSA compile(Writable<ABSCISSA>       &beta,
                                        const Readable<bool>     &used)
                {
                    // extract beta
                    Variables::ConstIterator it = vars->begin();
                    for(size_t i=vars->size();i>0;--i,++it)
                    {
                        const Variable &var = **it; if(!var[used]) continue;
                        var[beta] = (*var[betaAdd])();
                    }

                    // return D2 stored in addenda head
                    assert(dsqrAdd);
                    return (*dsqrAdd)();
                }

            };

        }

    }

}



#endif // !Y_MKL_Fit_Sample_Included

