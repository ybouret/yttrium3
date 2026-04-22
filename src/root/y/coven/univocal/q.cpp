
#include "y/coven/univocal.hpp"

namespace Yttrium
{

    namespace Coven
    {
        bool Univocal:: Make( Writable<apz> &target, const Readable<apq> &source )
        {
            //------------------------------------------------------------------
            //
            //
            // check according to dimensions
            //
            //
            //------------------------------------------------------------------
            assert(target.size()==source.size());
            const size_t dims = source.size();
            switch(dims)
            {
                case 0: return false;
                case 1:
                    if(__Zero__ == source[1].numer.s )
                    {
                        target[1] = 0;
                        return false;
                    }
                    else
                    {
                        target[1] = 1;
                        return true;
                    }
                default:
                    break;
            }

            //------------------------------------------------------------------
            //
            //
            // Initialize study
            //
            //
            //------------------------------------------------------------------
            assert(dims>=2);
            const apq   &last      = source[dims];
            SignType     firstSign = last.numer.s; // initialize
            size_t       numPos    = 0;            // #positive
            size_t       numNeg    = 0;            // #negative
            apz *        pnz       = 0;            // pointer to last non zero integer
            apn          lcm       = last.denom;   // initialize product

            switch(firstSign)
            {
                case Positive: ++numPos; pnz = &target[dims]; break;
                case Negative: ++numNeg; pnz = &target[dims]; break;
                case __Zero__: target[dims] = 0; assert(1==last.denom); break;
            }

            //------------------------------------------------------------------
            //
            //
            // first pass: update on remaining dimensions
            //
            //
            //------------------------------------------------------------------
            for(size_t i=dims-1;i>0;--i)
            {
                const apq &q = source[i];

                switch(q.numer.s)
                {
                    case __Zero__: target[i]=0; assert(1==q.denom); continue;
                    case Positive: ++numPos; firstSign = Positive; break;
                    case Negative: ++numNeg; firstSign = Negative; break;
                }

                pnz = &target[i];
                lcm = apn::LCM(lcm,q.denom);
            }
            //std::cerr << "lcm=" << lcm << std::endl;

            //------------------------------------------------------------------
            //
            //
            // check main status
            //
            //
            //------------------------------------------------------------------
            switch(numPos+numNeg)
            {
                case 0:
                    assert(0==numPos);
                    assert(0==numNeg);
                    assert(__Zero__==firstSign);
                    assert(!pnz);
                    return false;

                case 1: //specific case
                    assert(__Zero__!=firstSign);
                    assert(pnz);
                    *pnz = 1;
                    return true;

                default:
                    break;
            }

            //------------------------------------------------------------------
            //
            //
            // multiply by lcm and collect gcd
            //
            //
            //------------------------------------------------------------------
            apn g;
            for(size_t i=dims;i>0;--i)
            {
                const apq &q = source[i]; if( q.is0() ) continue;
                const apq  p = q * lcm;   assert( p.denom.is1() ); assert( !p.numer.is0() );
                const apz &z = (target[i]=p.numer);
                switch(g.bits())
                {
                    case 0: g = z.n; break;
                    case 1: break; // coprimes
                    default:
                        g = apn::GCD(g,z.n);
                        break;
                }
            }
            assert(g>0);
            //std::cerr << "g=" << g << std::endl;


            const unsigned flags
            = ( (g.bits()>1) ? SIMPLIFICATION : LEFT_UNTOUCHED )
            |     OppositeSigns(numPos,numNeg,firstSign);

            switch(flags)
            {
                case SIMPLIFICATION:
                    for(size_t i=dims;i>0;--i)
                    {
                        apz &z = target[i];
                        switch(z.s)
                        {
                            case __Zero__: continue;
                            case Negative:
                            case Positive:
                                Coerce(z.n) /= g;
                                continue;
                        }
                    }
                    break;

                case OPPOSITE_SIGNS:
                    for(size_t i=dims;i>0;--i) Sign::MakeOpposite( Coerce(target[i].s) );
                    break;

                case COUPLED_UPDATE:
                    for(size_t i=dims;i>0;--i)
                    {
                        apz &z = target[i];
                        switch(z.s)
                        {
                            case __Zero__: continue;
                            case Negative: Coerce(z.n) /= g; Coerce(z.s) = Positive; continue;
                            case Positive: Coerce(z.n) /= g; Coerce(z.s) = Negative; continue;
                        }
                    }
                    break;

                default:
                    assert(LEFT_UNTOUCHED==flags);
                    break;
            }

            return false;

        }
    }

}


