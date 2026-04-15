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

    }
}


