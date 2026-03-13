
//! \file

#ifndef Y_Memory_Metrics_Included
#define Y_Memory_Metrics_Included 1

#include "y/calculus/base2.hpp"
#include "y/calculus/integer-log2.hpp"

#if !defined(Y_BLOCK_SIZE)
//! default allocated block size
#define Y_BLOCK_SIZE 4096
#endif

namespace Yttrium
{
    namespace Memory
    {
        //______________________________________________________________________
        //
        //
        //! Various constants for allocation
        //
        //______________________________________________________________________
        struct Metrics
        {
            static const size_t   DefaultBytes = Y_BLOCK_SIZE;                     //!< default allocated page
            static const unsigned DefaultShift = IntegerLog2<DefaultBytes>::Value; //!< DefaultBytes=2^DefaultShift

            static const size_t   MinPageBytes = 256;                              //!< minimal allocated page size
            static const unsigned MinPageShift = IntegerLog2<MinPageBytes>::Value; //!< MinPageBytes=2^MinPageShift

            static const size_t   MaxPageBytes = Base2<size_t>::MaxBytes; //!< maximal allocated bytes
            static const unsigned MaxPageShift = Base2<size_t>::MaxShift; //!< MaxPageBytes=2^MaxPageShift

            static void Validate() noexcept; //!< used to perform static checks

        };
    }

}

#endif // !Y_Memory_Metrics_Included

