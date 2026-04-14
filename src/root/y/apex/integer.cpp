#include "y/apex/integer.hpp"
#include "y/swap.hpp"
#include "y/calculus/iabs.hpp"

namespace Yttrium
{
    namespace Apex
    {

        const char * const Integer::CallSign = "apz";

        Integer:: ~Integer() noexcept
        {
        }

        Integer:: Integer() :
        s(__Zero__),
        n()
        {

        }

        Integer:: Integer(const integer_t z) :
        s( Sign::Of(z) ),
        n( natural_t( IAbs(z) ) )
        {
            
        }


        Integer:: Integer(const Integer &z) :
        Number(),
        s(z.s),
        n(z.n)
        {
        }

        Integer:: Integer(const Natural &N) :
        s( N.bits() ? Positive : __Zero__),
        n(N)
        {
        }

        Integer & Integer:: xch( Integer & z) noexcept
        {
            CoerceSwap(s,z.s);
            Coerce(n).xch( Coerce(z.n) );
            return *this;
        }

        Integer & Integer:: operator=( const Integer &z )
        {
            Integer tmp(z);
            return xch(tmp);
        }

        Integer & Integer:: operator=( const Natural &N )
        {
            Integer tmp(N);
            return xch(tmp);
        }

        Integer & Integer:: operator=( const integer_t z ) noexcept
        {
            Coerce(s) = Sign::Of(z);
            Coerce(n) = (natural_t)IAbs(z);
            return *this;
        }

        Integer Natural:: operator-() const
        {
            Integer z(*this);
            if(bits()) Coerce(z.s) = Negative;
            return z;
        }

    }
}
