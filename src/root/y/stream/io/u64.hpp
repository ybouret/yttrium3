//! \file

#ifndef Y_Stream_IO_U64_Included
#define Y_Stream_IO_U64_Included 1

#include "y/config/setup.hpp"
#include "y/calculus/integer-log2.hpp"
#include "y/type/ints.hpp"

namespace Yttrium
{
    namespace IO
    {
        //______________________________________________________________________
        //
        //
        //
        //! common info for IO64 codec
        //
        //
        //______________________________________________________________________
        class U64Bits
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef uint64_t      Type;                                           //!< alias
            static const size_t   Size        = sizeof(Type);                     //!< size of type
            static const size_t   ExtraBytes  = Size;                             //!< maximum extra bytes
            static const size_t   HeaderBits  = IntegerLog2<ExtraBytes>::Value+1; //!< bits to store number of extra bytes
            static const size_t   SourceBits  = 8 - HeaderBits;                   //!< bits to store beginning of original data
            static const uint64_t ByteMask64  = 0xff;                             //!< alias
            static const uint64_t SourceMask  = ByteMask64 >> HeaderBits;           //!< to extract data

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit U64Bits() noexcept; //!< setup
            virtual ~U64Bits() noexcept; //!< cleanup

        private:
            Y_Disable_Copy_And_Assign(U64Bits); //!< discarded
        };
    }
}


#endif // !Y_Stream_IO_U64_Included

