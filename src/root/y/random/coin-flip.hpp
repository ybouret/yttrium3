
//! \file

#ifndef Y_Random_CoinFlip_Included
#define Y_Random_CoinFlip_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Random
    {

        class CoinFlip
        {
        public:
            explicit CoinFlip() noexcept;
            virtual ~CoinFlip() noexcept;

            virtual bool heads() noexcept = 0; //!< \return true if heads show
            virtual bool tails() noexcept;     //!< \return !heads

        private:
            Y_Disable_Copy_And_Assign(CoinFlip);
        };

    }

}

#endif // !Y_Random_CoinFlip_Included

