#include "y/apex/rational.hpp"
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


        void Rational:: reduce()
        {
            if( denom.is0() ) throw Libc::Exception(EDOM,"%s with zero denominator", CallSign);

            const Natural g = Natural::GCD(numer.n,denom);
            if(g>1)
            {
                Natural nn = numer.n / g;
                Natural dd = denom   / g;
                Coerce(numer.n).xch(nn);
                Coerce(denom).xch(dd);
            }

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

    }

}
