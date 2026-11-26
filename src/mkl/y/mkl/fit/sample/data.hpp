
//! \file

#ifndef Y_MKL_Fit_DataSample_Included
#define Y_MKL_Fit_DataSample_Included 1

#include "y/mkl/fit/sample.hpp"
#include "y/mkl/fit/type/write-xy.hpp"
#include "y/container/cxx/light-array.hpp"
#include "y/container/cxx/array.hpp"

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
            //! Sample of Data
            //
            //
            //__________________________________________________________________
            template <typename ABSCISSA, typename ORDINATE>
            class DataSample : public Sample<ABSCISSA,ORDINATE>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Sample<ABSCISSA,ORDINATE>           SampleType;     //!< alias
                typedef typename SampleType::FunctionType   FunctionType;   //!< alias
                typedef typename SampleType::GradientType   GradientType;   //!< alias
                typedef typename SampleType::AdditionType   AdditionType;   //!< alias
                typedef typename SampleType::AdditionHandle AdditionHandle; //!< alias

                using SampleType::checkCardinal;
                using SampleType::UpdateOnlyD2;
                using SampleType::updateEntire;
                using SampleType::access;
                using SampleType::vars;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param name compatible name
                 \param xa   first abscissa address
                 \param ya   first ordinate address
                 \param na   number of data
                 */
                template <typename NAME> inline
                explicit DataSample(const NAME &           name,
                                    const ABSCISSA * const xa,
                                    const ORDINATE * const ya,
                                    const size_t           na) :
                SampleType(name),
                x( (ABSCISSA *) xa, na ),
                y( (ORDINATE *) ya, na ),
                yf(na),
                tag(0)
                {
                    checkCardinal();
                }

                //! cleanup
                inline virtual ~DataSample() noexcept {}

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                inline virtual size_t cardinal() const noexcept
                {
                    assert( x.size() == y.size() );
                    assert( x.size() == yf.size() );
                    return x.size();
                }

                virtual void save(OutputStream &fp) const
                {
                    const size_t n = cardinal();
                    for(size_t i=1;i<=n;++i)
                        WriteXY<ABSCISSA,ORDINATE>::To(fp,x[i], y[i], yf[i], tag);
                }


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const LightArray<ABSCISSA> x;   //!< abscissae
                const LightArray<ORDINATE> y;   //!< ordinates
                CxxArray<ORDINATE>         yf;  //!< fitted ordinates
                const size_t               tag; //!< for I/O

            private:
                Y_Disable_Copy_And_Assign(DataSample); //!< discarded>

                
                inline virtual
                void gatherD2(AdditionType             & sumD2,
                              FunctionType             & F,
                              const Readable<ABSCISSA> & aorg)
                {
                    Y_Lock(access);
                    const size_t n = cardinal(); assert(n>0);
                    UpdateOnlyD2(sumD2,y[1],yf[1]=F.start(x[1],vars,aorg));
                    for(size_t i=2;i<=n;++i)
                        UpdateOnlyD2(sumD2,y[i],yf[i]=F.start(x[i],vars,aorg));
                }


                inline virtual
                void gatherD2(AdditionType             & sumD2,
                              Writable<AdditionHandle> & sumBeta,
                              Matrix<AdditionHandle>   & sumAlpha,
                              GradientType             & G,
                              const Readable<ABSCISSA> & aorg,
                              const Readable<bool>     & used,
                              Writable<ORDINATE>       & dFda)
                {
                    Y_Lock(access);
                    const size_t n = cardinal(); assert(n>0);
                    updateEntire(sumD2,sumBeta,sumAlpha,dFda,y[1],yf[1]=G.start(dFda,x[1],vars,aorg,used),used);
                    for(size_t i=2;i<=n;++i)
                        updateEntire(sumD2,sumBeta,sumAlpha,dFda,y[i],yf[i]=G.start(dFda,x[i],vars,aorg,used),used);
                }

            };




        }

    }
}

#endif // !Y_MKL_Fit_DataSample_Included


