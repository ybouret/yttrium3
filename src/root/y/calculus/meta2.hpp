//! \file

#ifndef Y_Calculus_Meta2_Included
#define Y_Calculus_Meta2_Included

#include "y/type/pick.hpp"
#include <cstdlib>

namespace Yttrium
{

    //! precompiled power-of-two flag
    template <size_t x> struct MetaIsPowerOfTwo
    {
        static const bool Result = (x && (!(x & (x - size_t(1) ) )) ); //!< true iff x=2^n
    };


    template <bool IsExact,size_t x> struct MetaLog2API;

    template <size_t x> struct MetaLog2API<true,x>
    {
        static const unsigned Value = 1 + MetaLog2API<true,(x>>1)>::Value;
    };

    template <> struct MetaLog2API<true,1>
    {
        static const unsigned Value = 0;
    };

    template <size_t x> struct MetaLog2API<false,x>
    {
        static const unsigned Value = 1 + MetaLog2API<false,(x>>1)>::Value;
    };

    template <> struct MetaLog2API<false,0>
    {
        static const unsigned Value = 0;
    };

    template <size_t x> struct MetaExactLog2
    {
        static const size_t Value =  MetaLog2API<true,x>::Value;
    };

    template <size_t x> struct MetaCeilLog2
    {
        static const size_t Value = MetaLog2API<MetaIsPowerOfTwo<x>::Result,x>::Value;
    };




    //! precompiled previous power-of-two
    template <size_t x> struct MetaPrevPowerOfTwo
    {
        //! meta-computed value
        static const size_t Value = MetaIsPowerOfTwo<x>::Result ? x : MetaPrevPowerOfTwo<x-1>::Value;
    };

    //! WRONG termination for MetaPrevPowerOfTwo
    template <> struct MetaPrevPowerOfTwo<0>
    {
        static const size_t Value = 0; //!< WRONG but necessary
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
