#include "y/apex/n/code.hpp"

namespace Yttrium
{
    namespace Apex
    {

        Natural & Natural:: shr() noexcept
        {
            assert(code);
            static_cast<KegType *>(code)->shr();
            return *this;
        }

        size_t Natural:: bits() const noexcept
        {
            assert(code);
            return static_cast<KegType *>(code)->bits;
        }
    }

}

