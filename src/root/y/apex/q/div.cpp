
#include "y/apex/rational.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Apex
    {

        Rational Rational:: Div(const Rational &lhs, const Rational &rhs)
        {
            switch( Sign::Pair(lhs.numer.s,rhs.numer.s))
            {
                case Sign::NZ:
                case Sign::PZ:
                case Sign::ZZ:
                    throw Libc:: Exception(EDOM,"%s division by zero",CallSign);

                case Sign::ZP:
                case Sign::ZN:
                    break;

                case Sign::PP:
                case Sign::NN:
                {
                    const Natural an = lhs.numer.n * rhs.denom;
                    const Natural dd = lhs.denom * rhs.numer.n;
                    return Rational(Positive,an,dd);
                };

                case Sign::NP:
                case Sign::PN: {
                    const Natural an = lhs.numer.n * rhs.denom;
                    const Natural dd = lhs.denom * rhs.numer.n;
                    return Rational(Negative,an,dd);
                }
            }
            
            return Rational();
        }

    }

}

