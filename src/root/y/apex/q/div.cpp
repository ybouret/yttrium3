
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
                    throw Libc:: Exception(EDOM,"%s: division by zero %s",CallSign, CallSign);

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

    namespace Apex
    {
        Rational Rational:: Div(const Rational &lhs, const Integer &rhs)
        {
            switch( Sign::Pair(lhs.numer.s,rhs.s))
            {
                case Sign::NZ:
                case Sign::PZ:
                case Sign::ZZ:
                    throw Libc:: Exception(EDOM,"%s: division by zero %s",CallSign, Integer::CallSign);

                case Sign::ZP:
                case Sign::ZN:
                    break; //!< zero

                case Sign::PP:
                case Sign::NN:
                {
                    const Natural dd = lhs.denom * rhs.n;
                    return Rational(Positive,lhs.numer.n,dd);
                };

                case Sign::NP:
                case Sign::PN: {
                    const Natural dd = lhs.denom * rhs.n;
                    return Rational(Negative,lhs.numer.n,dd);
                }
            }
            return Rational();
        }

        Rational Rational:: Div(const Integer &lhs, const Rational &rhs)
        {
            switch( Sign::Pair(lhs.s,rhs.numer.s))
            {
                case Sign::NZ:
                case Sign::PZ:
                case Sign::ZZ:
                    throw Libc:: Exception(EDOM,"%s: division by zero %s",Integer::CallSign, CallSign);

                case Sign::ZP:
                case Sign::ZN:
                    break;

                case Sign::PP:
                case Sign::NN:
                {
                    const Natural an = lhs.n * rhs.denom;
                    return Rational(Positive,an,rhs.numer.n);
                };

                case Sign::NP:
                case Sign::PN: {
                    const Natural an = lhs.n * rhs.denom;
                    return Rational(Negative,an,rhs.numer.n);
                }
            }
            return Rational();
        }

    }

    namespace Apex
    {

        Rational Rational:: Div(const Rational &lhs, const integer_t rhs)
        {
            switch( Sign::Pair(lhs.numer.s,Sign::Of(rhs)))
            {
                case Sign::NZ:
                case Sign::PZ:
                case Sign::ZZ:
                    throw Libc:: Exception(EDOM,"%s: division by zero integer_t",CallSign);

                case Sign::ZP:
                case Sign::ZN:
                    break; //!< zero

                case Sign::PP:
                case Sign::NP:
                {
                    const Natural dd = lhs.denom * (natural_t)rhs;
                    return Rational(lhs.numer.s,dd);
                }

                case Sign::PN:
                case Sign::NN:
                {
                    const Natural dd = lhs.denom * (natural_t)-rhs;
                    return Rational(lhs.numer.s,dd);
                }
                    
            }
            return Rational();
        }
    }




}

