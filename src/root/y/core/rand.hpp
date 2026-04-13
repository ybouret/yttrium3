
//! \file

#ifndef Y_Core_Rand_Included
#define Y_Core_Rand_Included 1

#include "y/random/coin-flip.hpp"
#include <cassert>
#include <cmath>

namespace Yttrium
{
    namespace Core
    {
        //______________________________________________________________________
        //
        //
        //
        //! basic portable uniform random number production
        //
        //
        //______________________________________________________________________
        class Rand : public Random:: CoinFlip
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Rand(const long init) noexcept; //!< setup \param init initial seed
            explicit Rand()                noexcept; //!< setup with time(NULL)
            virtual ~Rand()                noexcept; //!< cleanup


            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            //! uniform boolean choice \return 50% true
            virtual bool heads() noexcept;



            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            float operator()() noexcept; //!< query next uniform prn \return ]0:1[



            //! producing index less or equal to n
            /**
             \param n index
             \return uniform [0:n]
             */
            template <typename T> inline
            T leq(const T n) noexcept
            {
                return (T)floorf((float)n * (*this)() + 0.5f);
            }

            //! producing integer within given range
            /**
             \param lower lower value
             \param upper upper value
             \return uniform [lower:upper]
             */
            template <typename T> inline
            T in(const T lower, const T upper) noexcept
            {
                assert(upper >= lower);
                const T delta = (T)(upper - lower);
                return (T)(lower + leq<T>(delta));
            }


            //! generate random type
            /**
             \param nbits required bits
             \return random type with exactly nbits
             */
            template <typename T> inline
            T gen(const size_t nbits) noexcept
            {
                assert(nbits<=sizeof(T)*8);
                if(nbits<=0)
                    return 0;
                else
                {
                    T res = 1;
                    for(size_t i=nbits-1;i>0;--i)
                    {
                        res <<= 1;
                        if(heads())
                            res |=  1;
                    }
                    return res;
                }

            }



        private:
            Y_Disable_Copy_And_Assign(Rand); //!< discard
            long seed; //!< internal seed
        };
    }

}

#endif // !Y_Core_Rand_Included

