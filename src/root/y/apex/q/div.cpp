
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
                    assert(rhs>0);
                    const Natural dd = lhs.denom * (natural_t)rhs;
                    return Rational(lhs.numer,dd);
                }

                case Sign::PN:
                case Sign::NN:
                {
                    assert(rhs<0);
                    const Natural dd = lhs.denom * (natural_t)-rhs;
                    return Rational(Sign::Opposite(lhs.numer.s),lhs.numer.n,dd);
                }
            }


            return Rational();
        }

        Rational Rational:: Div(const integer_t lhs, const Rational &rhs)
        {
            switch( Sign::Pair( Sign::Of(lhs), rhs.numer.s) )
            {
                case Sign::PZ:
                case Sign::NZ:
                case Sign::ZZ:
                    throw Libc:: Exception(EDOM,"integer_t: division by zero %s",CallSign);

                case Sign::PN:
                case Sign::PP:
                {
                    assert(lhs>0);
                    const Natural nn = rhs.denom * (natural_t) lhs;
                    return Rational(rhs.numer.s,nn,rhs.numer.n);
                }

                case Sign::NN:
                case Sign::NP:
                {
                    assert(lhs<0);
                    const Natural nn = rhs.denom * ( (natural_t) -lhs );
                    return Rational( Sign::Opposite(rhs.numer.s),nn,rhs.numer.n);
                }

                case Sign::ZP:
                case Sign::ZN:
                    break; // => zero
            }

            return Rational();
        }
    }

    namespace Apex
    {
        Rational Rational:: Div(const Rational &lhs, const Natural &rhs)
        {

            switch(rhs.bits())
            {
                case 0: throw Libc:: Exception(EDOM,"%s: division by zero %s",CallSign,Natural::CallSign);
                case 1: assert(1==rhs); return lhs;
                default:
                    break;
            }

            const Natural dd = lhs.denom * rhs;
            return Rational(lhs.numer,dd);
        }


        Rational Rational:: Div(const Natural &lhs, const Rational &rhs)
        {
            switch(rhs.numer.s)
            {
                case __Zero__: throw Libc:: Exception(EDOM,"%s: division by zero %s",Natural::CallSign,CallSign);
                case Positive:
                case Negative:
                    break;
            }

            switch(lhs.bits())
            {
                case 0: return Rational();
                case 1: return Rational(rhs.numer.s,rhs.denom,rhs.numer.n);
                default:
                    break;
            }

            const Natural nn = lhs * rhs.denom;
            return Rational(rhs.numer.s,nn,rhs.numer.n);

        }

    }




}

