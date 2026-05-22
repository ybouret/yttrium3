
//! \file

#ifndef Y_Random_CoinFlip_Included
#define Y_Random_CoinFlip_Included 1

#include "y/config/setup.hpp"
#include "y/calculus/required-bits.hpp"
#include "y/check/static.hpp"
#include "y/type/is-signed-int.hpp"

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

            //! (slow) generate a random unsigned
            /**
             \param umax max value
             \return U in [0:umax]
             */
            template <typename U> inline U toss(const U umax)
            {
                Y_STATIC_CHECK(!IsSignedInt<U>::Value,BadType);
                const size_t bits = RequiredBitsFor(umax);
                while(true)
                {
                    U u = 0;
                    for(size_t i=bits;i>0;--i)
                    {
                        u <<= 1;
                        if(heads()) u|=1;
                    }
                    if(u<=umax) return u;
                }
            }

            template <typename T> inline T uniform()
            {
                static const T denom = 65536;
                static const T half(0.5f);
                uint16_t       numer = 0;
                for(size_t i=16;i>0;--i) { numer <<= 1; if(heads()) numer |= 1; }
                return (half + (T) numer)/denom;
            }



        private:
            Y_Disable_Copy_And_Assign(CoinFlip); //!< discarded
        };

    }

}

#endif // !Y_Random_CoinFlip_Included

