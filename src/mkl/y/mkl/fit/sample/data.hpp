
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

            template <typename ABSCISSA, typename ORDINATE>
            class DataSample : public Sample<ABSCISSA,ORDINATE>
            {
            public:
                typedef Sample<ABSCISSA,ORDINATE>          SampleType;
                typedef typename SampleType::FunctionType  FunctionType;
                typedef typename SampleType::AdditionType  AdditionType;

                using SampleType::checkSize;
                using SampleType::vars;

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
                    checkSize();
                }

                inline virtual ~DataSample() noexcept {}

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

                const LightArray<ABSCISSA> x;
                const LightArray<ORDINATE> y;
                CxxArray<ORDINATE>         yf;
                const size_t               tag;

            private:
                Y_Disable_Copy_And_Assign(DataSample);

                inline virtual void collectD2(AdditionType             & sumD2,
                                              FunctionType             & F,
                                              const Readable<ABSCISSA> & aorg)
                {
                    const size_t n = cardinal(); assert(n>0);
                    sumD2 << this->collect(y[1],yf[1] = F.start(x[1],vars,aorg));
                    for(size_t i=2;i<=n;++i)
                        sumD2 << this->collect(y[i],yf[i] = F.value(x[i],vars,aorg));
                }


            };




        }

    }
}

#endif // !Y_MKL_Fit_DataSample_Included


