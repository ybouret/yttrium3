#include "y/apex/rational.hpp"
#include "y/core/max.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Apex
    {

        const char * const Rational::CallSign = "apq";

        Rational:: Rational() : numer(), denom(1) {}

        Rational:: ~Rational() noexcept
        {
        }

        const char * Rational:: callSign() const noexcept
        {
            return CallSign;
        }

        void Rational:: ldz() noexcept
        {
            Coerce(numer).ldz();
            Coerce(denom) = 1;
        }


        bool Rational:: is0() const noexcept
        {
            return __Zero__ == numer.s;
        }

        bool Rational:: is1() const noexcept
        {
            return numer.is1() && denom.is1();
        }


        String Rational:: toDec() const
        {
            if(1==denom)
                return numer.toDec();
            else
            {
                String s = '(';
                s += numer.toDec();
                s += '/';
                s += denom.toDec();
                s += ')';
                return s;
            }
        }

        std::ostream & operator<<(std::ostream &os, const Rational &q)
        {
            return os << q.toDec();
        }


        Rational:: Rational(const Rational &q) :
        Number(),
        numer(q.numer),
        denom(q.denom)
        {
        }

        Rational:: Rational(const Integer &z) :
        Number(),
        numer(z),
        denom(1)
        {
        }

        Rational:: Rational(const Natural &n) :
        Number(),
        numer(n),
        denom(1)
        {
        }

        Rational:: Rational(const integer_t z) :
        Number(),
        numer(z),
        denom(1)
        {
        }

        Rational & Rational:: xch( Rational &q ) noexcept
        {
            Coerce(numer).xch( Coerce(q.numer) );
            Coerce(denom).xch( Coerce(q.denom) );
            return *this;
        }


        Integer::Integer(const Rational &q) :
        Number(),
        s(q.numer.s),
        n(q.numer.n)
        {
            if(q.denom<=1) throw Libc::Exception(EDOM,"rational is not integer");
        }

        Integer & Integer:: operator=( const Rational &q )
        {
            Integer tmp(q);
            return xch(tmp);
        }


        

        Rational:: Rational(const Integer &n, const Natural &d) :
        Number(),
        numer(n),
        denom(d)
        {
            reduce();
        }


        Rational:: Rational(const Integer &n, const natural_t d) :
        Number(),
        numer(n),
        denom(d)
        {
            reduce();
        }

        Rational:: Rational(const integer_t n, const Natural &d) :
        Number(),
        numer(n),
        denom(d)
        {
            reduce();
        }

        Rational:: Rational(const integer_t n, const natural_t d) :
        Number(),
        numer(n),
        denom(d)
        {
            reduce();
        }

        Rational:: Rational(const Fraction f) :
        Number(),
        numer(f.numer),
        denom(f.denom)
        {
            reduce();
        }

        Rational:: Rational(Random::CoinFlip &coin, const size_t nbits, const size_t dbits) :
        Number(),
        numer(coin,nbits),
        denom(coin,Max<size_t>(1,dbits))
        {
            reduce();
        }



    }

}
