#include "y/object/factory.hpp"
#include "y/memory/metrics.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(object)
{
    const unsigned MaxSlimShift = Memory::Metrics::MinPageShift-1;
    const size_t   MaxSlimBytes = 1<<MaxSlimShift;

    size_t last = 0;
    size_t count = 0;
    for(size_t i=1;i<=MaxSlimBytes;++i)
    {
        const size_t curr = Object::Factory::SlimCompress(i);
        std::cerr << std::setw(4) << i << " -> " << curr << std::endl;
        if(curr>last)
        {
            last = curr;
            ++count;
        }
    }
    std::cerr << "count = " << count << " / " << MaxSlimBytes << std::endl;

}
Y_UDONE()

