
#include "y/apex/integer.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Integer  Integer:: Mul(const Integer & lhs, const Integer & rhs)
        {
            switch( Sign::Pair(lhs.s,rhs.s) )
            {

                case Sign::PP:
                case Sign::NN:
                {
                    const Natural p = Natural::Mul(lhs.n,rhs.n);
                    return Integer(Positive,p);
                }

                case Sign::NP:
                case Sign::PN:
                {
                    const Natural p = Natural::Mul(lhs.n,rhs.n);
                    return Integer(Negative,p);
                }


                case Sign::PZ:
                case Sign::NZ:
                case Sign::ZN:
                case Sign::ZP:
                case Sign::ZZ:
                    break; // => zero
            }
            return Integer();
        }

        Integer  Integer:: Mul(const Integer & lhs, const Natural & rhs)
        {
            if(rhs.bits())
            {
                switch(lhs.s)
                {
                    case Negative:
                    case Positive: {
                        Integer res = lhs; Coerce(res.n) * rhs;
                        return res;
                    }

                    case __Zero__:
                        break;
                }
                return 0;
            }
            else
                return 0;
        }

        Integer  Integer:: Mul(const Natural & lhs, const Integer & rhs)
        {
            return Mul(rhs,lhs);
        }


        namespace
        {
            static inline natural_t _abs_of(const integer_t z) noexcept
            {
                return (z<0) ? (natural_t) -z : (natural_t)z;
            }
        }

        Integer  Integer:: Mul(const Integer & lhs, const integer_t rhs)
        {
            switch( Sign::Pair(lhs.s,Sign::Of(rhs)) )
            {

                case Sign::PP:
                case Sign::NN:
                {
                    const Natural p = Natural::Mul(lhs.n,_abs_of(rhs));
                    return Integer(Positive,p);
                }

                case Sign::NP:
                case Sign::PN:
                {
                    const Natural p = Natural::Mul(lhs.n,_abs_of(rhs));
                    return Integer(Negative,p);
                }


                case Sign::PZ:
                case Sign::NZ:
                case Sign::ZN:
                case Sign::ZP:
                case Sign::ZZ:
                    break; // => zero
            }
            return Integer();
        }

        Integer  Integer:: Mul(const integer_t lhs, const Integer & rhs)
        {
            return Mul(rhs,lhs);
        }


    }

}

