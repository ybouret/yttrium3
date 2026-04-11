
#include "y/apex/n/code.hpp"
#include "y/type/destroy.hpp"
#include "y/swap.hpp"

namespace Yttrium
{
    namespace Apex
    {

        const char * const       Natural:: CallSign = "apn";
        const char *             Natural:: callSign() const noexcept { return CallSign; }
        const Natural::Directly_ Natural:: Directly = {};

        Natural:: Natural() : code( new KegType() )
        {
        }

        Natural:: Natural(const Directly_ &, void * const handle) noexcept :
        code( handle )
        {
            assert(code);
        }

        Natural:: Natural(const natural_t n) : code( new KegType(CopyOf,n) )
        {
        }

        Natural:: Natural(const TwoToThePowerOf_ &_, const size_t n) : code( new KegType(_,n) )
        {
        }


        Natural:: ~Natural() noexcept
        {
            assert(code);
            delete (KegType *)code;
            Coerce(code) = 0;
        }

        Natural:: Natural(const Natural &n) :
        Number(),
        code( new KegType( *static_cast<const KegType *>(n.code) ) )
        {
        }
        
        Natural & Natural:: operator=( const Natural & n )
        {
            assert(code);
            void * temp = new KegType( *static_cast<const KegType *>(n.code) );
            delete (KegType *)code;
            Coerce(code) = temp;
            return *this;
        }

        Natural & Natural:: operator=( const natural_t n )
        {
            assert(code);
            static_cast<KegType *>(code)->assign(n);
            return *this;
        }

        Natural & Natural:: xch(Natural &n) noexcept
        {
            assert(code);
            assert(n.code);
            CoerceSwap(code,n.code);
            return *this;
        }

        String Natural:: toHex() const
        {
            return static_cast<const KegType *>(code)->toHex();
        }

        std::ostream & operator<<(std::ostream &os, const Natural &n)
        {
            return os << n.toHex();
        }

        natural_t Natural:: lsw() const noexcept
        {
            return static_cast<const KegType *>(code)->getNatural();
        }

    }

}
