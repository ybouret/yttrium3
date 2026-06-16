
//! \file

#ifndef Y_Random_Uniform32_Included
#define Y_Random_Uniform32_Included 1

#include "y/random/coin-flip.hpp"

namespace Yttrium
{
    namespace Random
    {
        //______________________________________________________________________
        //
        //
        //
        //! 32-bits uniform generator
        //
        //
        //______________________________________________________________________
        class Uniform32
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Uniform32(const uint32_t) noexcept; //!< setup with max32
            virtual ~Uniform32()               noexcept; //!< cleanup

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


            template <typename T> T to() noexcept; //!< \return value for ...

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const uint32_t max32; //!< 32 bits in [0:max32]
            const double   denom; //!< max32 + 1
        private:
            Y_Disable_Copy_And_Assign(Uniform32); //!< discarded
        };

    }
}

#endif // !Y_Random_Uniform32_Included
