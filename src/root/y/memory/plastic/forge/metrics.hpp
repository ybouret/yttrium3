
//! \file

#ifndef Y_Memory_Plastic_Forge_Metrics_Included
#define Y_Memory_Plastic_Forge_Metrics_Included 1

#include "y/memory/plastic/bricks.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium
{

    namespace Memory
    {
        namespace Plastic
        {
            //! metrics for Forge and Object::Factory
            struct ForgeMetrics
            {
                static const size_t BrickOffset  = Alignment::To<Brick>::CeilOf<sizeof(Bricks)>::Value; //!< offset of data within allocated Bricks
                static const size_t ReservedSize = BrickOffset + Bricks::Reserved;                      //!< used data within Bricks
            };
        }

    }

}

#endif // !Y_Memory_Plastic_Forge_Metrics_Included
