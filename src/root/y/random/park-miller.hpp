
//! \file

#ifndef Y_Random_Park_Miller_Included
#define Y_Random_Park_Miller_Included 1

#include "y/random/bits.hpp"

namespace Yttrium
{
    namespace Random
    {
        //______________________________________________________________________
        //
        //
        //
        //! Minimal Uniform Generator
        //
        //
        //______________________________________________________________________
        class ParkMiller : public Bits
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "ParkMiller"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit ParkMiller();           //!< setup with random seed
            virtual ~ParkMiller() noexcept;  //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual uint32_t     next32() noexcept;
            virtual const char * callSign() const noexcept;

        private:
            Y_Disable_Copy_And_Assign(ParkMiller); //!< discarded
            long seed; //!< inner seed
        };
    }

}

#endif // !Y_Random_Park_Miller_Included
