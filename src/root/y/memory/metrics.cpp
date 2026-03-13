#include "y/memory/metrics.hpp"
#include "y/check/static.hpp"

namespace Yttrium
{
    namespace Memory
    {
        void Metrics:: Validate() noexcept
        {
            Y_STATIC_CHECK(MinPageBytes<MaxPageBytes,  InvalidMinMax);
            Y_STATIC_CHECK(DefaultBytes<MaxPageBytes,  DefaultTooBig);
            Y_STATIC_CHECK(DefaultBytes>=MinPageBytes, DefaultTooLow);
        }
    }

}
