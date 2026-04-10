
#include "y/apex/n/code.hpp"
#include "y/type/destroy.hpp"
#include "y/swap.hpp"

namespace Yttrium
{
    namespace Apex
    {

        const char * const Natural:: CallSign = "apn";

        const char * Natural:: callSign() const noexcept { return CallSign; }

        Natural:: Natural() : code( new KegType() )
        {
        }


        Natural:: Natural(const natural_t n) : code( new KegType(CopyOf,n) )
        {
        }


        Natural:: ~Natural() noexcept
        {
            delete (KegType *)code;
            Coerce(code) = 0;
        }

        Natural:: Natural(const Natural &n) :
        code( new KegType( *static_cast<const KegType *>(n.code) ) )
        {
        }
        
        Natural & Natural:: operator=( const Natural & n )
        {
            void * temp = new KegType( *static_cast<const KegType *>(n.code) );
            delete (KegType *)code;
            Coerce(code) = temp;
            return *this;
        }

        Natural & Natural:: xch(Natural &n) noexcept
        {
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

    }

}
