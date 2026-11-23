#include "y/mkl/fit/sample/metrics.hpp"
#include "y/stream/libc/output.hpp"
#include "y/exception.hpp"

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

            void SampleMetrics:: autoSave() const
            {
                const String fileName = *this + ".dat";
                OutputFile   fp(fileName);
                save(fp);
            }


        }

    }

}
