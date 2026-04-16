#include "y/apex/integer.hpp"
#include "y/swap.hpp"
#include "y/calculus/iabs.hpp"


namespace Yttrium
{
    namespace Apex
    {

        const char * const Integer::CallSign = "apz";

        const char * Integer:: callSign() const noexcept
        {
            return CallSign;
        }

        void Integer:: ldz() noexcept
        {
            Coerce(s) = __Zero__;
            Coerce(n).ldz();
        }

        Integer:: Integer(const SignType S, const Natural &N) :
        s(S),
        n(N)
        {
            switch(s)
            {
                case Negative: assert( N.bits() > 0 );  break;
                case __Zero__: assert( 0 == N.bits() ); break;
                case Positive: assert( N.bits() > 0 ); break;
            }
        }

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



        std::ostream & operator<<(std::ostream &os, const Integer &z)
        {
            switch(z.s)
            {
                case Negative: return os << ('-' + z.n.toDec() );
                case __Zero__:
                case Positive:
                    break;
            }
            return os << z.n.toDec();
        }


        bool Integer:: is0() const noexcept
        {
            return __Zero__ == s;
        }

        Integer::Integer(Random::CoinFlip &coin, const size_t nbits) :
        s(__Zero__),
        n(coin,nbits)
        {
            if(n.bits())
            {
                if( coin.heads() ) Coerce(s) = Positive; else Coerce(s) = Negative;
            }
        }
    }
}
