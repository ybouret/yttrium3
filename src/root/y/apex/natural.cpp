
#include "y/apex/n/code.hpp"
#include "y/type/destroy.hpp"
#include "y/swap.hpp"

namespace Yttrium
{
    namespace Apex
    {

        const char * const Natural:: CallSign = "apn";



        Natural:: Natural() : code( new KegType() )
        {
        }


        Natural:: ~Natural() noexcept
        {
            delete (KegType *)code;
            Coerce(code) = 0;
        }

        Natural:: Natural(const Natural &n) :
        code( new KegType( *(KegType *)(n.code) ) )
        {
        }
        
        Natural & Natural:: operator=( const Natural & n )
        {
            void * temp = new KegType( *(KegType *)(n.code) );
            delete (KegType *)code;
            Coerce(code) = temp;
            return *this;
        }

        Natural & Natural:: xch(Natural &n) noexcept
        {
            CoerceSwap(code,n.code);
            return *this;
        }

    }

}
