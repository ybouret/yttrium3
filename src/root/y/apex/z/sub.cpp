#include "y/apex/integer.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Integer Integer:: operator-() const
        {
            Integer z = *this;
            Sign::MakeOpposite( Coerce(z.s) );
            return z;
        }

        Integer Integer:: Sub(const Integer &lhs, const Integer &rhs)
        {
            switch( Sign::Pair(lhs.s,rhs.s) )
            {
                case Sign::NZ:
                case Sign::PZ:
                    return lhs;

                case Sign::ZN:
                case Sign::ZP:
                    return -rhs;

                case Sign:: PN: { const Natural sum = lhs.n + rhs.n; assert(sum>0); return Integer(Positive,sum); }
                case Sign:: NP: { const Natural sum = lhs.n + rhs.n; assert(sum>0); return Integer(Negative,sum); }

                case Sign:: PP:
                    switch( Sign::Of(lhs.n,rhs.n) )
                    {
                        case Negative: { const Natural delta = rhs.n - lhs.n; assert(delta>0); return Integer(Negative,delta); }
                        case Positive: { const Natural delta = lhs.n - rhs.n; assert(delta>0); return Integer(Positive,delta); }
                        case __Zero__: break; // => zero
                    }
                    break; // => zero

                case Sign:: NN:
                    switch( Sign::Of(lhs.n,rhs.n) )
                    {
                        case Negative: { const Natural delta = rhs.n - lhs.n; assert(delta>0); return Integer(Positive,delta); }
                        case Positive: { const Natural delta = lhs.n - rhs.n; assert(delta>0); return Integer(Negative,delta); }
                        case __Zero__: break; // => zero
                    }
                    break; // => zero

                case Sign::ZZ:
                    break;
            }

            // zero
            return Integer();
        }

    }

}

