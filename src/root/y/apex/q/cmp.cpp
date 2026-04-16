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

    }

}

