#include "y/coven/univocal.hpp"

namespace Yttrium
{

    namespace Coven
    {
        

        bool Univocal:: Make( Writable<apz> & array )
        {
            //------------------------------------------------------------------
            //
            //
            // check according to dimensions
            //
            //
            //------------------------------------------------------------------
            const size_t size = array.size();
            switch(size)
            {
                case 0: return true;
                case 1: {
                    apz &z = array[1];
                    if(__Zero__!=z.s)
                    {
                        z=1;
                        return true;
                    }
                    else
                        return false;
                }
                default:
                    break;
            } assert(size>=2);

            //------------------------------------------------------------------
            //
            //
            // Initialize study
            //
            //
            //------------------------------------------------------------------
            apz         &last      = array[size]; // last value to start with
            SignType     firstSign = last.s;      // initialize
            size_t       numPos    = 0;           // #positive
            size_t       numNeg    = 0;           // #negative
            apn          g         = last.n;      // default gcd
            apz *        pnz       = 0;           // pointer to last non zero

            switch(firstSign)
            {
                case Positive: ++numPos; pnz = &last; break;
                case Negative: ++numNeg; pnz = &last; break;
                case __Zero__: break;
            }

            //------------------------------------------------------------------
            //
            //
            // update on remaining dimensions
            //
            //
            //------------------------------------------------------------------
            for(size_t i=size-1;i>0;--i)
            {
                apz &z = array[i];
                switch(z.s)
                {
                    case Positive: ++numPos; firstSign = Positive; break;
                    case Negative: ++numNeg; firstSign = Negative; break;
                    case __Zero__: continue;
                }
                if(pnz)
                    g = apn::GCD(g, (pnz = &z)->n);
                else
                    g = (pnz = &z)->n;
            }


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
                    assert(0==g);
                    assert(0==numPos);
                    assert(0==numNeg);
                    assert(__Zero__==firstSign);
                    assert(!pnz);
                    return false;

                case 1: //specific case
                    assert(0!=g);
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
            // detect and perform operations
            //
            //
            //------------------------------------------------------------------
            assert(g>0);
            assert(g.bits()>=1);
            assert(numPos>0||numNeg>0);
            assert(pnz);
            assert(__Zero__!=firstSign);

            const unsigned flags
            = ( (g.bits()>1) ? SIMPLIFICATION : LEFT_UNTOUCHED )
            |     OppositeSigns(numPos,numNeg,firstSign);

            switch(flags)
            {
                case SIMPLIFICATION:
                    for(size_t i=size;i>0;--i)
                    {
                        apz &z = array[i];
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
                    for(size_t i=size;i>0;--i) Sign::MakeOpposite( Coerce(array[i].s) );
                    break;

                case COUPLED_UPDATE:
                    for(size_t i=size;i>0;--i)
                    {
                        apz &z = array[i];
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


            return true;
        }
    }

}

