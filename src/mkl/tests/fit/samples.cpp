#include "y/mkl/fit/variables.hpp"
#include "y/utest/run.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/container/matrix.hpp"

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
            //! SampleMetrics
            //
            //
            //__________________________________________________________________
            class SampleMetrics : public String
            {
            public:
                template <typename NAME> inline
                explicit SampleMetrics(const NAME &name) :
                String(name),
                vars()
                {
                }

                virtual ~SampleMetrics() noexcept;

                
                virtual size_t size() const noexcept = 0;
                void           checkSize() const;
                Variables      vars;


            private:
                Y_Disable_Copy_And_Assign(SampleMetrics);

            };

        }

    }

}



namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            void SampleMetrics:: checkSize() const
            {
                if( size() <= 0 ) throw Specific::Exception(c_str(),"empty sample");
            }

            SampleMetrics:: ~SampleMetrics() noexcept
            {
            }

        }

    }

}


namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            template <typename ABSCISSA, typename ORDINATE>
            class Function
            {
            public:

                inline explicit Function() noexcept {}
                inline virtual ~Function() noexcept {}

                virtual ORDINATE start(const ABSCISSA &, const Variables &, const Readable<ABSCISSA> &) = 0;
                virtual ORDINATE value(const ABSCISSA &, const Variables &, const Readable<ABSCISSA> &) = 0;

            private:
                Y_Disable_Copy_And_Assign(Function);
            };
        }

    }
}

#include "y/cameo/addition.hpp"


namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            template <typename ABSCISSA, typename ORDINATE>
            class Sample : public SampleMetrics
            {
            public:
                typedef Function<ABSCISSA,ORDINATE> FunctionType;
                typedef Cameo::Addition<ABSCISSA>   XAddtionType;

                template <typename NAME> inline
                explicit Sample(const NAME &name) : SampleMetrics(name)
                {

                }

                inline virtual ~Sample() noexcept {}

                inline ABSCISSA D2(FunctionType &F)
                {
                    xadd.free();
                    gatherD2(F);
                    return xadd.sum();
                }

                XAddtionType xadd;

            private:
                Y_Disable_Copy_And_Assign(Sample);

                virtual void collectD2(FunctionType &F, const Readable<ABSCISSA> &aorg) = 0;
                inline void collect(const ORDINATE &lhs, const ORDINATE &rhs)
                {

                }
            };

        }

    }

}

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
                using SampleType::checkSize;
                using SampleType::vars;

                template <typename NAME> inline
                explicit DataSample(const NAME &name,
                                    const ABSCISSA * const xa,
                                    const ORDINATE * const ya,
                                    const size_t           na) :
                SampleType(name),
                x( (ABSCISSA *) xa, na ),
                y( (ORDINATE *) ya, na ),
                yf(na)
                {
                    checkSize();
                }

                inline virtual ~DataSample() noexcept {}

                inline virtual size_t size() const noexcept
                {
                    assert( x.size() == y.size() );
                    return x.size();
                }


                const LightArray<ABSCISSA> x;
                const LightArray<ORDINATE> y;
                CxxArray<ORDINATE>         yf;


            private:
                Y_Disable_Copy_And_Assign(DataSample);
                virtual void collectD2(FunctionType &F, const Readable<ABSCISSA> &aorg)
                {
                    const size_t n = size(); assert(n>0);
                    collect(y[1],yf[1] = F.start(x[1],vars,aorg));
                    for(size_t i=2;i<=n;++i)
                        collect(y[i],yf[i] = F.value(x[1],vars,aorg));
                }
            };

        }

    }
}





using namespace Yttrium;
using namespace MKL;

namespace
{
    static const double _t1[]    = { 30,80,140,200,270,320,430,550,640,720,830,890 };
    static const double _x1[]    = { 4.414520,5.011710,5.632319,6.194379,6.721311,7.330211,8.009368,8.735363,9.297424,9.707260,10.339578,10.878220};
    static const size_t _n1      = sizeof(_t1)/sizeof(_t1[0]);

    static const double _t2[]    = { 60,120,200,270,360,460,580,670,790,920,1040 };
    static const double _x2[]    = { 5.199063,5.854801,6.662763,7.365340,8.067916,8.782201,9.578454,10.175644,10.878220,11.651054,12.213115};
    static const size_t _n2      = sizeof(_t2)/sizeof(_t2[0]);
}

Y_UTEST(fit_samples)
{




}
Y_UDONE()

