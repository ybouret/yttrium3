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


    namespace Core
    {
        template <bool IsExact,size_t x> struct MetaLog2API;

        //! generic Log2 for power-of-two integer
        template <size_t x> struct MetaLog2API<true,x>
        {
            static const unsigned Value = 1 + MetaLog2API<true,(x>>1)>::Value; //!< recursive value
        };

        //! termination for power-of-two integer
        template <> struct MetaLog2API<true,1>
        {
            static const unsigned Value = 0; //!< terminal value
        };

        //! generic Log2 for NOT power-of-two integer
        template <size_t x> struct MetaLog2API<false,x>
        {
            static const unsigned Value = 1 + MetaLog2API<false,(x>>1)>::Value; //!< recursive value
        };

        //! termination for NOT power-of-two integer
        template <> struct MetaLog2API<false,0>
        {
            static const unsigned Value = 0; //!< terminal value
        };

        template <bool> struct MetaAccept;

        //! accept the instance
        template <> struct MetaAccept<true>
        {
            typedef const int Type; //!< will set to 1
        };

        //! reject the instance
        template <> struct MetaAccept<false>
        {
            typedef const void * Type; //!< won't set to 1
        };

    }


    //! check exact value
    template <size_t x> struct MetaExactLog2
    {
        typedef typename Core::MetaAccept< MetaIsPowerOfTwo<x>::Result >::Type IsExactLog2; //!< alias
        static IsExactLog2  Check = 1; //!< only possible when exact log2
        static const size_t Value = Core::MetaLog2API<true,x>::Value; //!< compute value
    };

    //! ceil log2
    template <size_t x> struct MetaCeilLog2
    {
        static const size_t Value = Core::MetaLog2API<MetaIsPowerOfTwo<x>::Result,x>::Value; //!< compute value
    };


    //! computed next power of two
    template <size_t x> struct MetaNextPowerOfTwo
    {
        static const  bool     IsExact = MetaIsPowerOfTwo<x>::Result;            //!< true iff exact log2
        static const unsigned  RawLog2 = Core::MetaLog2API<IsExact,x>::Value;    //!< compute from API
        static const size_t    _1      = 1;                                      //!< alias
        static const size_t    Value   = _1 << ( IsExact ? RawLog2 : RawLog2+1); //!< detec
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

#if 0
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
#endif

}

#endif // !Y_Calculus_Meta2_Included
