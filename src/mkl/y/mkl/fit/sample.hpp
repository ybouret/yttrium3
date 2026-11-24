//! \file

#ifndef Y_MKL_Fit_Sample_Included
#define Y_MKL_Fit_Sample_Included 1

#include "y/mkl/fit/sample/metrics.hpp"
#include "y/mkl/fit/type/function.hpp"
#include "y/mkl/fit/type/gradient.hpp"
#include "y/cameo/addition.hpp"
#include "y/cameo/addenda.hpp"
#include "y/mkl/api/mod2.hpp"

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
                typedef Cameo::Addition<ABSCISSA>    AdditionType; //!< alias
                typedef Cameo::Addenda<ABSCISSA>     AddendaType;  //!< alias
                typedef Keyed<String,ArcPtr<Sample>> Pointer;      //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param name compatible name
                template <typename NAME> inline
                explicit Sample(const NAME &name) :
                SampleMetrics(name),
                addenda()
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

                //! collect D2 contribution
                /**
                 \param sumD2 target addition
                 \param F     fit function
                 \param aorg  current parameters
                 */
                virtual void collectD2(AdditionType             &sumD2,
                                       FunctionType             &F,
                                       const Readable<ABSCISSA> &aorg) = 0;



             

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
                    AdditionType &xadd = * addenda.make(1);
                    xadd.ldz();
                    collectD2(xadd,F,atry);
                    return xadd();
                }

                //______________________________________________________________
                //
                //
                // Members+
                //
                //______________________________________________________________
                //AdditionType xadd;    //!< addition helper
                AddendaType  addenda; //!< addition helper

            private:
                Y_Disable_Copy_And_Assign(Sample); //!< dicarded

            protected:
                //! helper for squared module
                /**
                 \param lhs lhs ordinate
                 \param rhs rhs ordinate
                 \return |lhs-rhs|^2 as abscissa
                 */
                inline ABSCISSA localD2(const ORDINATE &lhs, const ORDINATE &rhs)
                {
                    const ORDINATE delta = lhs-rhs;
                    return Mod2<ORDINATE>(delta);
                }
            };

        }

    }

}



#endif // !Y_MKL_Fit_Sample_Included

