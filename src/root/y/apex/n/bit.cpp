#include "y/apex/n/code.hpp"
#include "y/swap.hpp"

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

        Natural & Natural:: shr(const size_t n) noexcept
        {
            assert(code);
            static_cast<KegType *>(code)->shr(n);
            return *this;
        }

        size_t Natural:: bits() const noexcept
        {
            assert(code);
            return static_cast<const KegType *>(code)->bits;
        }

        Natural &Natural:: shl()
        {
            assert(code);
            void * temp = static_cast<const KegType *>(code)->shl();
            delete static_cast<KegType *>(code);
            Coerce(code) = temp;
            return *this;
        }

        Natural &Natural:: shl(const size_t n)
        {
            assert(code);
            void * temp = static_cast<const KegType *>(code)->shl(n);
            delete static_cast<KegType *>(code);
            Coerce(code) = temp;
            return *this;
        }
    }

}

