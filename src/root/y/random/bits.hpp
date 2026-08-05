
//! \file

#ifndef Y_Random_Uniform32_Included
#define Y_Random_Uniform32_Included 1

#include "y/random/coin-flip.hpp"
#include "y/mkl/xreal.hpp"

namespace Yttrium
{
    namespace Random
    {

        template <typename T> struct Alea;

        //! select T for XReal<T>
        template <typename T> struct Alea< XReal<T> > { typedef T Type; /*!< alias */ };

        //! select T for real T
        template <typename T> struct Alea { typedef T Type; /*!< alias */ };


        //______________________________________________________________________
        //
        //
        //
        //! 32-bits uniform generator
        //
        //
        //______________________________________________________________________
        class Bits
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Bits(const uint32_t) noexcept; //!< setup with max32
            virtual ~Bits()               noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual uint32_t next32() noexcept = 0; //!< \return next 32 bits word in [0:max32]

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            double operator()() noexcept; //!< \return uniform ]0:1[
            double symm32()     noexcept; //!< \return uniform ]-1:1[

            template <typename T> T to()   noexcept; //!< \return value for ...
            template <typename T> T symm() noexcept;



            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const uint32_t max32; //!< 32 bits in [0:max32]
            const double   denom; //!< max32 + 1
        private:
            Y_Disable_Copy_And_Assign(Bits); //!< discarded
        };

    }
}

#endif // !Y_Random_Uniform32_Included
