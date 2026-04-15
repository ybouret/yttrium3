
#include "y/apex/integer.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Integer Integer:: operator+() const
        {
            return *this;
        }

        Integer Integer:: Add(const Integer &lhs, const Integer &rhs)
        {
            switch( Sign::Pair(lhs.s,rhs.s) )
            {
                case Sign::PP: { const Natural sum = lhs.n+rhs.n; return Integer(Positive,sum); }
                case Sign::NN: { const Natural sum = lhs.n+rhs.n; return Integer(Negative,sum); }

                case Sign::ZP:
                case Sign::ZN:
                    return rhs;

                case Sign::PZ:
                case Sign::NZ:
                    return lhs;

                case Sign::PN:
                {
                    switch( Natural::Cmp(lhs.n,rhs.n) )
                    {
                        case Negative: { const Natural delta = rhs.n - lhs.n; return Integer(Negative,delta); }
                        case Positive: { const Natural delta = lhs.n - rhs.n; return Integer(Positive,delta); }
                        case __Zero__:
                            break; // => zero
                    }
                } break; // => zero

                case Sign::NP:
                {
                    switch( Natural::Cmp(lhs.n,rhs.n) )
                    {
                        case Negative: { const Natural delta = rhs.n - lhs.n; return Integer(Positive,delta); }
                        case Positive: { const Natural delta = lhs.n - rhs.n; return Integer(Negative,delta); }
                        case __Zero__:
                            break; // => zero
                    }
                } break; // => zero


                case Sign::ZZ: // ==> zero
                    break;
            }
            // zero
            return Integer();
        }

    }

}

