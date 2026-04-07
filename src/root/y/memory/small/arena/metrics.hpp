
//! \file

#ifndef Y_Memory_Small_Arena_Metrics_Included
#define Y_Memory_Small_Arena_Metrics_Included 1

#include "y/config/compiler.h"

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {

            //! "public" part of Arena Metrics
            struct ArenaMetrics
            {
                static const size_t   _1                = 1;                    //!< alias
                static const unsigned MinNumBlocksLog2  = 4;                    //!< to ensure MinNumBlocks is a power of two
                static const size_t   MinNumBlocks      = _1<<MinNumBlocksLog2; //!< Minimal Blocks in Chunk
                static const size_t   MaxNumBlocks      = 255;                  //!< Maximal Blocks in Chunk
                static const size_t   DataLocation      = 8 * sizeof(void*);    //!< Chunk requires 5 * sizeof(void*)
            };

        }

    }

}


#endif // !Y_Memory_Small_Arena_Metrics_Included

