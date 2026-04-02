//! \file

#ifndef Y_Calculus_Meta2_Included
#define Y_Calculus_Meta2_Included

#include "y/type/pick.hpp"
#include <cstdlib>

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //! precompiled power-of-two flag
    //
    //__________________________________________________________________________
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

    //__________________________________________________________________________
    //
    //! compute for exact power of two value
    //__________________________________________________________________________
    template <size_t x> struct MetaExactLog2
    {
        typedef typename Core::MetaAccept< MetaIsPowerOfTwo<x>::Result >::Type IsExactLog2; //!< alias
        static IsExactLog2  Check = 1; //!< only possible when exact log2
        static const size_t Value = Core::MetaLog2API<true,x>::Value; //!< compute value
    };

    //__________________________________________________________________________
    //
    //! ceil log2
    //__________________________________________________________________________
    template <size_t x> struct MetaCeilLog2
    {
        static const size_t Value = Core::MetaLog2API<MetaIsPowerOfTwo<x>::Result,x>::Value; //!< compute value
    };

    //__________________________________________________________________________
    //
    //! computed next power of two
    //__________________________________________________________________________
    template <size_t x> struct MetaNextPowerOfTwo
    {
        static const size_t    _1    = 1;                             //!< alias
        static const size_t    Value = _1 << MetaCeilLog2<x>::Value; //!< computed value
    };

    //__________________________________________________________________________
    //
    //! computed prev power of two
    //__________________________________________________________________________
    template <size_t x> struct MetaPrevPowerOfTwo
    {
        typedef typename Core::MetaAccept< (x>0) >::Type IsPossible;                 //!< alias
        static const IsPossible Check    = 1;                                        //!< will block x=0
        static const bool       IsExact  = MetaIsPowerOfTwo<x>::Result;              //!< true iff exact log2
        static const unsigned   CeilLog2 = MetaCeilLog2<x>::Value;                   //!< ceil log2
        static const size_t     _1       = 1;                                        //!< alias
        static const size_t     Value    = _1 << ( IsExact ? CeilLog2 : CeilLog2-1); //!< deduce value
    };


}

#endif // !Y_Calculus_Meta2_Included
