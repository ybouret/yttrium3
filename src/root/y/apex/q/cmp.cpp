#include "y/apex/rational.hpp"

namespace Yttrium
{
    namespace Apex
    {
        bool operator==(const Rational &lhs, const Rational &rhs) noexcept
        {
            return lhs.denom == rhs.denom && lhs.numer == lhs.numer;
        }

        bool operator==(const Rational &lhs, const Integer &rhs) noexcept
        {
            return lhs.denom == 1 && lhs.numer == rhs;
        }

        bool operator==(const Rational &lhs, const integer_t rhs) noexcept
        {
            return lhs.denom == 1 && lhs.numer == rhs;
        }

        bool operator==(const Integer &lhs, const Rational &rhs) noexcept
        {
            return  1 == rhs.denom && lhs == rhs.numer;
        }

        bool operator==(const integer_t lhs, const Rational &rhs) noexcept
        {
            return  1 == rhs.denom && lhs == rhs.numer;
        }

        bool operator==(const Rational &lhs, const Natural &rhs) noexcept
        {
            return lhs.denom == 1 && lhs.numer == rhs;
        }

        bool operator==(const Natural &lhs, const Rational &rhs) noexcept
        {
            return  1 == rhs.denom && lhs == rhs.numer;
        }


    }

    namespace Apex
    {
        bool operator!=(const Rational &lhs, const Rational &rhs) noexcept
        {
            return lhs.denom != rhs.denom || lhs.numer != lhs.numer;
        }

        bool operator!=(const Rational &lhs, const Integer &rhs) noexcept
        {
            return lhs.denom != 1 || lhs.numer != rhs;
        }

        bool operator!=(const Rational &lhs, const integer_t rhs) noexcept
        {
            return lhs.denom != 1 || lhs.numer != rhs;
        }

        bool operator!=(const Integer &lhs, const Rational &rhs) noexcept
        {
            return  1 != rhs.denom || lhs != rhs.numer;
        }

        bool operator!=(const integer_t lhs, const Rational &rhs) noexcept
        {
            return  1 != rhs.denom || lhs != rhs.numer;
        }

        bool operator!=(const Rational &lhs, const Natural &rhs) noexcept
        {
            return lhs.denom != 1 || lhs.numer != rhs;
        }

        bool operator!=(const Natural &lhs, const Rational &rhs) noexcept
        {
            return  1 != rhs.denom || lhs != rhs.numer;
        }

    }


    namespace Apex
    {
        SignType Rational:: Cmp(const Rational &lhs, const Rational &rhs)
        {

            switch( Sign::Pair(lhs.numer.s,rhs.numer.s))
            {

                case Sign::PZ:
                case Sign::PN:
                case Sign::ZN:
                    return Positive;

                case Sign::ZP:
                case Sign::NP:
                case Sign::NZ:
                    return Negative;

                case Sign::ZZ:
                    return __Zero__;

                case Sign::PP:
                case Sign::NN:
                    break;
            }
            
            const Integer L = lhs.numer * rhs.denom;
            const Integer R = rhs.numer * lhs.denom;
            return Integer::Cmp(L,R);
        }

        SignType Rational:: Cmp(const Rational &lhs, const Integer &rhs)
        {
            const Integer R = rhs * lhs.denom;
            return Integer::Cmp(lhs.numer,R);
        }

        SignType Rational:: Cmp(const Integer &lhs, const Rational &rhs)
        {
            return Sign::Opposite( Cmp(rhs,lhs) );
        }

        SignType Rational:: Cmp(const Rational &lhs, const Natural &rhs)
        {
            const Integer R = rhs * lhs.denom;
            return Integer::Cmp(lhs.numer,R);
        }

        SignType Rational:: Cmp(const Natural &lhs, const Rational &rhs)
        {
            return Sign::Opposite( Cmp(rhs,lhs) );
        }

        SignType Rational:: Cmp(const Rational &lhs, const integer_t rhs)
        {
            return __Zero__;
        }

        SignType Rational:: Cmp(const integer_t lhs, const Rational &rhs)
        {
            return Sign::Opposite( Cmp(rhs,lhs) );
        }

        

    }
}


