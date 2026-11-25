//! \file

#ifndef Y_MKL_Fit_Sample_Included
#define Y_MKL_Fit_Sample_Included 1

#include "y/mkl/fit/sample/metrics.hpp"
#include "y/mkl/fit/type/function.hpp"
#include "y/mkl/fit/type/gradient.hpp"
#include "y/cameo/addition.hpp"
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
                typedef AdditionType *               AdditionHandle; //!< alias
                typedef Keyed<String,ArcPtr<Sample>> Pointer;      //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup with at least one AdditionType \param name compatible name
                template <typename NAME> inline
                explicit Sample(const NAME &name) :
                SampleMetrics(name)
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
                    sumD2.ldz();
                    gatherD2(sumD2,F,aorg);
                    return sumD2();
                }


            private:
                Y_Disable_Copy_And_Assign(Sample); //!< dicarded

            protected:
                static inline void UpdateD2(AdditionType &sumD2, const ORDINATE &y, const ORDINATE &yf)
                {
                    const ORDINATE delta = y - yf;
                    sumD2 << delta*delta;
                }
            };

        }

    }

}



#endif // !Y_MKL_Fit_Sample_Included

