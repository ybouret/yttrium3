//! \file

#ifndef Y_Calculus_Meta2_Included
#define Y_Calculus_Meta2_Included

#include <cstdlib>

namespace Yttrium
{

    //! precompiled power-of-two flag
    template <size_t x> struct MetaIsPowerOfTwo
    {
        static const bool Result = (x && (!(x & (x - size_t(1) ) )) ); //!< true iff x=2^n
    };

    //! precompiled previous power-of-two
    template <size_t x> struct MetaPrevPowerOfTwo
    {
        static const size_t Value = MetaIsPowerOfTwo<x>::Result ? x : MetaPrevPowerOfTwo<x-1>::Value;
    };

    //! WRONG termination for MetaPrevPowerOfTwo
    template <> struct MetaPrevPowerOfTwo<0>
    {
        static const size_t Value = 0;
    };

    //! precompiled next power-of two
    template <size_t x> struct MetaNextPowerOfTwo
    {
        //! trick to avoid infinite recursion
        static const size_t Value = MetaIsPowerOfTwo<x>::Result ? x : (MetaPrevPowerOfTwo<x>::Value<<1);
    };

    //! termination for MetaNextPowerOfTwo
    template <> struct MetaNextPowerOfTwo<0>
    {
        static const size_t Value = 1; //!< special case
    };


}

#endif // !Y_Calculus_Meta2_Included
