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
                    switch( Natural::Cmp(lhs.n,rhs.n) )
                    {
                        case Negative: { const Natural delta = rhs.n - lhs.n; assert(delta>0); return Integer(Negative,delta); }
                        case Positive: { const Natural delta = lhs.n - rhs.n; assert(delta>0); return Integer(Positive,delta); }
                        case __Zero__: break; // => zero
                    }
                    break; // => zero

                case Sign:: NN:
                    switch( Natural::Cmp(lhs.n,rhs.n) )
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


        Integer Integer:: Sub(const Integer &lhs, const Natural &rhs)
        {
            if(rhs.bits())
            {
                switch(lhs.s)
                {
                    case __Zero__: break; // => -rhs
                    case Negative: { Integer res = lhs; Coerce(res.n) += rhs; return res; }
                    case Positive:
                        switch( Natural::Cmp(lhs.n,rhs) )
                        {
                            case Positive: { const Natural delta = lhs.n - rhs; assert(delta>0); return Integer(Positive,delta); }
                            case Negative: { const Natural delta = rhs - lhs.n; assert(delta>0); return Integer(Negative,delta); }
                            case __Zero__: break; // => zero
                        }
                        return Integer();
                }
                assert(0==lhs.n);
                return Integer(Negative,rhs);
            }
            else
            {
                return lhs;
            }
        }

        Integer Integer:: Sub(const Natural &lhs, const Integer &rhs)
        {
            if(lhs.bits())
            {
                switch(rhs.s)
                {
                    case Negative: { Integer res = -rhs; Coerce(res.n) += lhs; return res; }
                    case Positive:
                        switch( Natural::Cmp(lhs,rhs.n) )
                        {
                            case Positive: { const Natural delta = lhs - rhs.n; assert(delta>0); return Integer(Positive,delta); }
                            case Negative: { const Natural delta = rhs.n - lhs; assert(delta>0); return Integer(Negative,delta); }
                            case __Zero__: break; // => zero
                        }
                        return Integer();
                    case __Zero__: break; // => lhs
                }

                assert(0==rhs.n);
                return lhs;
            }
            else
            {
                return -rhs;
            }
        }

        Integer  Integer:: Sub(const Integer & lhs, const integer_t rhs)
        {
            return Add(lhs,-rhs);
        }

        Integer  Integer:: Sub(const integer_t lhs, const Integer & rhs)
        {
            Integer res = Add(rhs,-lhs);
            Sign::MakeOpposite( Coerce(res.s) );
            return res;
        }

    }

}

