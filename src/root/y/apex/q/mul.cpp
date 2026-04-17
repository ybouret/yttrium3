
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
    }

}

