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
                case Sign::PP: { const Natural sum = lhs.n+rhs.n; assert(sum>0); return Integer(Positive,sum); }
                case Sign::NN: { const Natural sum = lhs.n+rhs.n; assert(sum>0); return Integer(Negative,sum); }

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
                        case Negative: { const Natural delta = rhs.n - lhs.n; assert(delta>0); return Integer(Negative,delta); }
                        case Positive: { const Natural delta = lhs.n - rhs.n; assert(delta>0); return Integer(Positive,delta); }
                        case __Zero__:
                            break; // => zero
                    }
                } break; // => zero

                case Sign::NP:
                {
                    switch( Natural::Cmp(lhs.n,rhs.n) )
                    {
                        case Negative: { const Natural delta = rhs.n - lhs.n; assert(delta>0); return Integer(Positive,delta); }
                        case Positive: { const Natural delta = lhs.n - rhs.n; assert(delta>0); return Integer(Negative,delta); }
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


        Integer Integer:: Add(const Integer &lhs, const Natural &rhs)
        {
            if(rhs.bits())
            {
                switch(lhs.s)
                {
                    case Negative:
                        switch( Natural::Cmp(lhs.n,rhs) )
                        {
                            case Negative: { const Natural delta = rhs - lhs.n; return Integer(Positive,delta); }
                            case Positive: { const Natural delta = lhs.n - rhs; return Integer(Negative,delta); }
                            case __Zero__: break;
                        }
                        return Integer();

                    case Positive:
                    { Integer res = lhs; Coerce(res.n) += rhs; return res; }

                    case __Zero__:
                        break;
                }
                return rhs;
            }
            else
                return lhs;
        }


        Integer Integer:: Add(const Natural &lhs, const Integer &rhs)
        {
            return Add(rhs,lhs);
        }

        Integer  Integer:: Add(const Integer & lhs, const integer_t rhs)
        {
            const SignType rs = Sign::Of(rhs);

            switch( Sign::Pair(lhs.s,rs) )
            {

                case Sign::ZZ:
                    break; // => zero
            }

            // zero
            return Integer();
        }

    }

}

