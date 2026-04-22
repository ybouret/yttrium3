#include "y/coven/univocal.hpp"

namespace Yttrium
{

    namespace Coven
    {

        namespace
        {
            static const unsigned IS_READY = 0x00;
            static const unsigned SIMPLIFY = 0x01;
            static const unsigned OPPOSITE = 0x02;
            static const unsigned BOTH_OPS = SIMPLIFY | OPPOSITE;

            static inline
            unsigned ChangeSigns(const size_t numPos,
                                 const size_t numNeg,
                                 const SignType firstSign) noexcept
            {
                assert(numPos>0||numNeg>0);
                assert(__Zero__!=firstSign);
                if( (numNeg>numPos) || ( (numPos==numNeg) && firstSign == Negative ) )
                {
                    //std::cerr << "should opposite" << std::endl;
                    return OPPOSITE;
                }
                else
                {
                    return IS_READY;
                }
            }

        };


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


            //std::cerr << "[+]=" << numPos << " [-]=" << numNeg << " g=" << g << ", firstSign=" << firstSign << std::endl;


            unsigned flags = IS_READY;
            switch(g.bits())
            {
                case 0:
                    assert(0==g);
                    assert(0==numPos);
                    assert(0==numNeg);
                    assert(__Zero__==firstSign);
                    assert(!pnz);
                    return false;

                case 1:
                    assert(1==g);
                    assert(numPos>0||numNeg>0);
                    assert(__Zero__!=firstSign);
                    break;

                default:
                    assert(1<g);
                    assert(numPos>0||numNeg>0);
                    assert(__Zero__!=firstSign);
                    flags |= SIMPLIFY;
                    break;
            }

            flags |= ChangeSigns(numPos,numNeg,firstSign);

            switch(flags)
            {
                case SIMPLIFY:
                    std::cerr << "[SIMPLIFY]" << std::endl;
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

                case OPPOSITE:
                    std::cerr << "[OPPOSITE]" << std::endl;
                    for(size_t i=size;i>0;--i) Sign::MakeOpposite( Coerce(array[i].s) );
                    break;

                case BOTH_OPS:
                    std::cerr << "[BOTH_OPS]" << std::endl;
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
                    assert(IS_READY==flags);
                    std::cerr << "[IS_READY]" << std::endl;
                    break;
            }


            return true;
        }
    }

}

