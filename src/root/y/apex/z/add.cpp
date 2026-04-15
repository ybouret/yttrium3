#include "y/apex/integer.hpp"
#include <iostream>

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

        namespace
        {
            static inline natural_t _abs_of(const integer_t z) noexcept
            {
                return z<0 ? (natural_t) -z : (natural_t)z;
            }
        }

        Integer  Integer:: Add(const Integer & lhs, const integer_t rhs)
        {
            switch( Sign::Pair(lhs.s,Sign::Of(rhs)) )
            {
                case Sign::ZP:
                case Sign::ZN:
                    return rhs;

                case Sign::PZ:
                case Sign::NZ:
                    return lhs;

                case Sign::PP: { const Natural sum = lhs.n+_abs_of(rhs); assert(sum>0); return Integer(Positive,sum); }
                case Sign::NN: { const Natural sum = lhs.n+_abs_of(rhs); assert(sum>0); return Integer(Negative,sum); }

                case Sign::PN:
                {
                    const natural_t N = _abs_of(rhs);
                    switch( Natural::Cmp(lhs.n,N) )
                    {
                        case Negative: { const Natural delta = N - lhs.n; assert(delta>0); return Integer(Negative,delta); }
                        case Positive: { const Natural delta = lhs.n - N; assert(delta>0); return Integer(Positive,delta); }
                        case __Zero__:
                            break; // => zero
                    }
                } break; // => zero

                case Sign::NP:
                {
                    const natural_t N = _abs_of(rhs);
                    switch( Natural::Cmp(lhs.n,rhs) )
                    {
                        case Negative: { const Natural delta = N - lhs.n; assert(delta>0); return Integer(Positive,delta); }
                        case Positive: { const Natural delta = lhs.n - N; assert(delta>0); return Integer(Negative,delta); }
                        case __Zero__:
                            break; // => zero
                    }
                } break; // => zero

                case Sign::ZZ:
                    break; // => zero
            }

            // zero
            return Integer();
        }

        Integer  Integer:: Add(const integer_t lhs, const Integer & rhs)
        {
            return Add(rhs,lhs);
        }

        Integer  Integer:: successor() const
        {
            switch(s)
            {
                case Negative:
                    if(1==n)
                    {
                        return Integer();
                    }
                    else
                    {
                        assert(n>=2);
                        Integer res = *this; --Coerce(res.n); return res;
                    }
                case Positive: { Integer res = *this; ++Coerce(res.n); return res; }
                case __Zero__:
                    break;
            }
            return 1;
        }

        Integer & Integer:: operator++()
        {
            Integer tmp = successor();
            return xch(tmp);
        }

        Integer Integer:: operator++(int)
        {
            const Integer res = *this;
            { Integer tmp = successor(); (void) xch(tmp); }
            return res;
        }
    }

}

