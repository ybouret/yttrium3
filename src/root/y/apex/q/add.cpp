
#include "y/apex/rational.hpp"

namespace Yttrium
{
    namespace Apex
    {

        Rational Rational:: operator+() const
        {
            return *this;
        }

        Rational Rational:: Add(const Rational &lhs, const Rational &rhs)
        {
            switch( Sign::Pair(lhs.numer.s,rhs.numer.s) )
            {
                case Sign::PZ:
                case Sign::NZ:
                    return lhs;

                case Sign::ZP:
                case Sign::ZN:
                    return rhs;

                case Sign::ZZ:
                    return Rational();

                case Sign::PP:
                case Sign::PN:
                case Sign::NP:
                case Sign::NN:
                    break;
            }
            const Integer nn = lhs.numer * rhs.denom + rhs.numer * lhs.denom;
            const Natural dd = rhs.denom * lhs.denom;
            return Rational(nn,dd);
        }

    }

    namespace Apex
    {
        Rational Rational:: Add(const Rational &lhs, const Integer &rhs)
        {
            switch( Sign::Pair(lhs.numer.s,rhs.s) )
            {
                case Sign::PZ:
                case Sign::NZ:
                    return lhs;

                case Sign::ZP:
                case Sign::ZN:
                    return rhs;

                case Sign::ZZ:
                    return Rational();

                case Sign::PP:
                case Sign::PN:
                case Sign::NP:
                case Sign::NN:
                    break;
            }
            const Integer nn = lhs.numer+ rhs * lhs.denom;
            return Rational(nn,lhs.denom);
        }


        Rational Rational:: Add(const Integer &lhs, const Rational &rhs)
        {
            return Add(rhs,lhs);
        }
    }

    namespace Apex
    {
        Rational Rational:: Add(const Rational &lhs, const Natural &rhs)
        {
            if( rhs.is0() )
            {
                return lhs;
            }
            else
            {
                switch(lhs.numer.s)
                {
                    case __Zero__:
                        return rhs;
                    case Positive:
                    case Negative:
                        break;
                }
                const Integer nn = lhs.numer + rhs * lhs.denom;
                return Rational(nn,lhs.denom);
            }
        }

        Rational Rational:: Add(const Natural &lhs, const Rational &rhs)
        {
            return Add(rhs,lhs);
        }

    }


    namespace Apex
    {
        Rational Rational:: Add(const Rational &lhs, const integer_t rhs)
        {
            switch( Sign::Pair(lhs.numer.s, Sign::Of(rhs) ) )
            {
                case Sign::PZ:
                case Sign::NZ:
                    return lhs;

                case Sign::ZP:
                case Sign::ZN:
                    return rhs;

                case Sign::PP:
                case Sign::NP: {
                    const Integer nn = lhs.numer + ( (natural_t)rhs * lhs.denom );
                    return Rational(nn,lhs.denom);
                }

                case Sign::NN:
                case Sign::PN: {
                    const Integer nn = lhs.numer - ( (natural_t)(-rhs) * lhs.denom );
                    return Rational(nn,lhs.denom);
                }

                case Sign::ZZ:
                    break; // => zero
            }
            return Rational();
        }

        Rational Rational:: Add(const integer_t lhs, const Rational &rhs)
        {
            return Add(rhs,lhs);
        }
    }


}
