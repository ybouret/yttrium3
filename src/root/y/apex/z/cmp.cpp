#include "y/apex/integer.hpp"

namespace Yttrium
{
    namespace Apex
    {

        SignType Integer:: Cmp(const Integer &lhs, const Integer &rhs) noexcept
        {
            switch( Sign::Pair(lhs.s,rhs.s) )
            {
                case Sign::ZP:
                case Sign::NP:
                case Sign::NZ:
                    return Negative;

                case Sign::PZ:
                case Sign::PN:
                case Sign::ZN:
                    return Positive;

                case Sign::PP: return Natural::Cmp(lhs.n,rhs.n);
                case Sign::NN: return Natural::Cmp(rhs.n,lhs.n);

                case Sign::ZZ:
                    break; // => zero
            }

            // zero
            return __Zero__;
        }


        SignType Integer:: Cmp(const Integer &lhs, const Natural &rhs) noexcept
        {
            const SignType l = lhs.s;
            if(rhs.bits())
            {
                assert(rhs>0);
                switch(l)
                {
                    case __Zero__:
                    case Negative:
                        return Negative;
                    case Positive:
                        break;
                }
                return Natural::Cmp(lhs.n,rhs);
            }
            else
            {
                assert(0==rhs);
                return l;
            }

        }


        SignType Integer:: Cmp(const Natural &lhs, const Integer &rhs) noexcept
        {
            return Sign::Opposite( Cmp(rhs,lhs) );
        }

        namespace {
            static inline natural_t _abs_of(const integer_t z) noexcept
            {
                return (z<0) ? (natural_t)-z : (natural_t)z;
            }
        }

        SignType Integer:: Cmp(const Integer &lhs, const integer_t rhs) noexcept
        {
            const SignType  r_s = Sign::Of(rhs);

            switch( Sign::Pair(lhs.s,r_s) )
            {
                case Sign::ZP:
                case Sign::NP:
                case Sign::NZ:
                    return Negative;

                case Sign::PZ:
                case Sign::PN:
                case Sign::ZN:
                    return Positive;

                case Sign::PP: return Natural::Cmp(lhs.n,_abs_of(rhs));
                case Sign::NN: return Natural::Cmp(_abs_of(rhs),lhs.n);

                case Sign::ZZ:
                    break; // => zero
            }

            return __Zero__;
        }

        SignType Integer:: Cmp(const integer_t lhs, const Integer &rhs) noexcept
        {
            return Sign::Opposite( Cmp(rhs,lhs) );
        }


    }
}


