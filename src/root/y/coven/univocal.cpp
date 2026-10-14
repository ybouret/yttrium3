
#include "y/coven/univocal.hpp"

namespace Yttrium
{

    namespace Coven
    {
        const unsigned Univocal:: LEFT_UNTOUCHED;
        const unsigned Univocal:: SIMPLIFICATION;
        const unsigned Univocal:: OPPOSITE_SIGNS;
        const unsigned Univocal:: COUPLED_UPDATE;

        unsigned Univocal:: OppositeSigns(const size_t numPos,
                                          const size_t numNeg,
                                          const SignType firstSign) noexcept
        {
            assert(numPos>0||numNeg>0);
            assert(__Zero__!=firstSign);
            if( (numNeg>numPos) || ( (numPos==numNeg) && firstSign == Negative ) )
            {
                return OPPOSITE_SIGNS;
            }
            else
            {
                return LEFT_UNTOUCHED;
            }
        }
    }

}


