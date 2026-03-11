//! \file

#ifndef Y_Type_Ints_Included
#define Y_Type_Ints_Included 1

#include "y/config/compiler.h"

namespace Yttrium
{
    template <typename T> struct UnsignedInt;


    //! Metrics for uint8_t
    template <>
    struct UnsignedInt<uint8_t>
    {
        typedef uint8_t   Type;           //!< alias
        static const Type Minimum = 0x00; //!< alias
        static const Type Maximum = 0xff; //!< alias
    };

    //! Metrics for uint16_t
    template <>
    struct UnsignedInt<uint16_t>
    {
        typedef uint16_t  Type;             //!< alias
        static const Type Minimum = 0x0000; //!< alias
        static const Type Maximum = 0xffff; //!< alias
    };

    //! Metrics for uint32_t
    template <>
    struct UnsignedInt<uint32_t>
    {
        typedef uint32_t  Type;                 //!< alias
        static const Type Minimum = 0x00000000; //!< alias
        static const Type Maximum = 0xffffffff; //!< alias
    };

    //! Metrics for uint64_t
    template <>
    struct UnsignedInt<uint64_t>
    {
        typedef uint64_t  Type;                            //!< alias
        static const Type Minimum = 0x0000000000000000ULL; //!< alias
        static const Type Maximum = 0xffffffffffffffffULL; //!< alias
    };


    template <typename T> struct SignedInt;

    //! Metrics for int8_t
    template <>
    struct SignedInt<int8_t>
    {
        typedef int8_t    Type;           //!< alias
        static const Type Minimum = -128; //!< alias
        static const Type Maximum =  127; //!< alias
    };

    //! Metrics for int16_t
    template <>
    struct SignedInt<int16_t>
    {
        typedef int16_t   Type;             //!< alias
        static const Type Minimum = -32768; //!< alias
        static const Type Maximum =  32767; //!< alias
    };


    //! Metrics for int32_t
    template <>
    struct SignedInt<int32_t>
    {
        typedef int32_t   Type;                      //!< alias
        static const Type Minimum = -2147483647L-1L; //!< alias
        static const Type Maximum =  2147483647L;    //!< alias
    };

    //! Metrics for int64_t
    template <>
    struct SignedInt<int64_t>
    {
        typedef int64_t    Type;                                 //!< alias
        static const Type  Minimum = -9223372036854775807LL-1LL; //!< alias
        static const Type  Maximum =  9223372036854775807LL;     //!< alias
    };

}

#endif // !Y_Type_Ints_Included
