#include "y/container.hpp"
#include "y/type/ints.hpp"
#include "y/system/exception.hpp"
#include <cerrno>
#include "y/calculus/alignment.hpp"
#include "y/core/max.hpp"

namespace Yttrium
{
    Container:: Container() noexcept
    {
    }

    Container:: ~Container() noexcept
    {
    }

    size_t Container:: NextCapacity(const size_t n)
    {
        static const size_t MinimumCapacity = 8;
        static const size_t MaximumCapacity = IntegerFor<size_t>::Maximum;
        if(n>=MaximumCapacity) throw Libc::Exception(EDOM,"Container Reached Maximum Capacity");
        const size_t increase = Max(Alignment::SystemMemory::Ceil(n>>1),MaximumCapacity-n);
        return Max(MinimumCapacity,n+increase);
    }


}

