
#include "y/random/coin-flip.hpp"

namespace Yttrium
{
    namespace Random
    {

        CoinFlip:: CoinFlip() noexcept
        {
        }


        CoinFlip:: ~CoinFlip() noexcept
        {
        }

        bool CoinFlip:: tails() noexcept
        {
            return ! heads();
        }

        
    }
}
