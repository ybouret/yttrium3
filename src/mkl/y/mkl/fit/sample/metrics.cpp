#include "y/mkl/fit/sample/metrics.hpp"
#include "y/stream/libc/output.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            void SampleMetrics:: checkCardinal() const
            {
                if( cardinal() <= 0 ) throw Specific::Exception(c_str(),"empty sample");
            }

            SampleMetrics:: ~SampleMetrics() noexcept
            {
            }

            void SampleMetrics:: autoSave() const
            {
                const String fileName = *this + ".dat";
                OutputFile   fp(fileName);
                save(fp);
            }

            size_t  SampleMetrics:: AdditionTypeCount(const size_t nvar)
            {
                assert(nvar>0);
                return 1+nvar + (nvar*(1+nvar))/2;
            }
        }

    }

}
