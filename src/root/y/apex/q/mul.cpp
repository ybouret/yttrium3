
#include "y/apex/rational.hpp"

namespace Yttrium
{
    namespace Apex
    {

        Rational Rational::Mul(const Rational &lhs, const Rational &rhs)
        {
            switch( Sign::Pair(lhs.numer.s,rhs.numer.s))
            {
                case Sign::NZ:
                case Sign::PZ:
                case Sign::ZN:
                case Sign::ZP:
                case Sign::ZZ:
                    return Rational();

                case Sign::NN:
                case Sign::NP:
                case Sign::PN:
                case Sign::PP:
                    break;
            }

            const Integer nn = lhs.numer * rhs.numer; assert(nn.n.bits()>0);
            if( lhs.denom.is1() )
            {
                assert(1==lhs.denom);
                if(rhs.denom.is1())
                {
                    assert(1==rhs.denom);
                    return nn;
                }
                else
                {
                    assert(rhs.denom>1);
                    return Rational(nn,rhs.denom);
                }
            }
            else
            {
                assert(lhs.denom>1);
                if(rhs.denom.is1())
                {
                    assert(1==rhs.denom);
                    return Rational(nn,lhs.denom);
                }
                else
                {
                    assert(rhs.denom>1);
                    const Natural dd = lhs.denom * rhs.denom;
                    return Rational(nn,dd);
                }
            }

        }
    }


    namespace Apex
    {
        Rational Rational::Mul(const Rational &lhs, const Integer &rhs)
        {
            switch( Sign::Pair(lhs.numer.s,rhs.s))
            {
                case Sign::NZ:
                case Sign::PZ:
                case Sign::ZN:
                case Sign::ZP:
                case Sign::ZZ:
                    return Rational();

                case Sign::NN:
                case Sign::NP:
                case Sign::PN:
                case Sign::PP:
                    break;
            }

            const Integer nn = lhs.numer * rhs;
            if(lhs.denom.is1())
            {
                assert(1==lhs.denom);
                return Rational(nn);
            }
            else
            {
                return Rational(nn,lhs.denom);
            }
        }

        Rational Rational:: Mul(const Integer &lhs, const Rational &rhs)
        {
            return Mul(rhs,lhs);
        }
    }

    namespace Apex
    {
        Rational Rational::Mul(const Rational &lhs, const integer_t rhs)
        {
            switch( Sign::Pair(lhs.numer.s,Sign::Of(rhs)) )
            {
                case Sign::NZ:
                case Sign::PZ:
                case Sign::ZN:
                case Sign::ZP:
                case Sign::ZZ:
                    return Rational();

                case Sign::NN:
                case Sign::NP:
                case Sign::PN:
                case Sign::PP:
                    break;
            }

            const Integer nn = lhs.numer * rhs;
            if(lhs.denom.is1())
            {
                assert(1==lhs.denom);
                return Rational(nn);
            }
            else
            {
                return Rational(nn,lhs.denom);
            }
        }

        Rational Rational:: Mul(const integer_t lhs, const Rational &rhs)
        {
            return Mul(rhs,lhs);
        }


    }

    namespace Apex
    {
        Rational Rational::Mul(const Rational &lhs, const Natural &rhs)
        {

            switch( rhs.bits() )
            {
                case 0: return Rational();
                case 1: return lhs;
                default:
                    break;
            }
            const Integer nn = lhs.numer * rhs;
            return Rational(nn,lhs.denom);

        }

        Rational Rational:: Mul(const Natural &lhs, const Rational &rhs)
        {
            return Mul(rhs,lhs);
        }
    }
}



