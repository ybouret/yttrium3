
//! \file

#ifndef Y_Memory_Plastic_Forge_Metrics_Included
#define Y_Memory_Plastic_Forge_Included 1

#include "y/memory/plastic/bricks.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium
{

    namespace Memory
    {
        namespace Plastic
        {
            struct ForgeMetrics
            {
                static const size_t BrickOffset  = Alignment::To<Brick>::CeilOf<sizeof(Bricks)>::Value; //!< offset of data
                static const size_t ReservedSize = BrickOffset + Bricks::Reserved;                      //!< alias

            };
        }

    }

}

#endif // !Y_Memory_Plastic_Forge_Metrics_Included
