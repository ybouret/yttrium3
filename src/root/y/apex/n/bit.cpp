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

        size_t Natural:: bytes() const noexcept
        {
            assert(code);
            return static_cast<const KegType *>(code)->bytes;
        }

        uint8_t Natural:: get(const size_t ibyte) const noexcept
        {
            assert(code);
            return static_cast<const KegType *>(code)->getByte(ibyte);
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



namespace Yttrium
{
    namespace Apex
    {

        Natural & Natural:: operator <<=( const size_t n )
        {
            Natural tmp = shl(n);
            return xch(tmp);
        }

        Natural & Natural:: operator >>=( const size_t n )
        {
            Natural tmp = shr(n);
            return xch(tmp);
        }


        Natural  operator<<(const Natural &x, const size_t s)
        {
            Natural res = x;
            return res.shl(s);
        }

        Natural  operator>>(const Natural &x, const size_t s)
        {
            Natural res = x;
            return res.shr(s);
        }
        
    }

    

}
