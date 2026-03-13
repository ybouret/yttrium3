
//! \file

#ifndef Y_Memory_Metrics_Included
#define Y_Memory_Metrics_Included 1

#include "y/calculus/base2.hpp"
#include "y/calculus/integer-log2.hpp"

#if !defined(Y_BLOCK_SIZE)
#define Y_BLOCK_SIZE 4096
#endif

namespace Yttrium
{
    namespace Memory
    {
        struct Metrics
        {
            static const size_t   DefaultBytes = Y_BLOCK_SIZE;
            static const unsigned DefaultShift = IntegerLog2<DefaultBytes>::Value;

            static const size_t   MinPageBytes = 256;
            static const unsigned MinPageShift = IntegerLog2<MinPageBytes>::Value;

            static const size_t   MaxPageBytes = Base2<size_t>::MaxBytes;
            static const unsigned MaxPageShift = Base2<size_t>::MaxShift;

            static void Validate() noexcept;

        };
    }

}

#endif // !Y_Memory_Metrics_Included

