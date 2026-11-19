
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

            class SampleMetrics : public String
            {
            public:
                template <typename NAME> inline
                explicit SampleMetrics(const NAME &name) : String(name)
                {
                }

                virtual ~SampleMetrics() noexcept;

                virtual size_t size() const noexcept = 0;


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

            template <typename ABSCISSAE, typename ORDINATES>
            class Sample : public SampleMetrics
            {
            public:

                template <typename NAME> inline
                explicit Sample(const NAME &name) : SampleMetrics(name)
                {

                }

                inline virtual ~Sample() noexcept {}
                
                virtual ORDINATES operator()(const size_t i, const Variables &) = 0;

            private:
                Y_Disable_Copy_And_Assign(Sample);
            };

        }

    }

}



using namespace Yttrium;
using namespace MKL;



Y_UTEST(fit_samples)
{




}
Y_UDONE()

