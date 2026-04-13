
//! \file

#ifndef Y_Random_CoinFlip_Included
#define Y_Random_CoinFlip_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Random
    {
        //______________________________________________________________________
        //
        //
        //
        //! Coin Flip experiment
        //
        //
        //______________________________________________________________________
        class CoinFlip
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit CoinFlip() noexcept; //!< setup
            virtual ~CoinFlip() noexcept; //!M cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual bool heads() noexcept = 0; //!< \return true if heads show
            virtual bool tails() noexcept;     //!< \return !heads

        private:
            Y_Disable_Copy_And_Assign(CoinFlip); //!< discarded
        };

    }

}

#endif // !Y_Random_CoinFlip_Included

