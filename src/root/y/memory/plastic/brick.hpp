//! \file

#ifndef Y_Memory_Plastic_Brick_Included
#define Y_Memory_Plastic_Brick_Included 1

#include "y/config/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Plastic
        {
            class Bricks;
            
            struct Brick
            {
                Bricks * used;
                size_t   size;
                Brick *  next;
                Brick *  prev;

                void updateSize() noexcept;

            };
        }
    }
}

#endif // !Y_Memory_Plastic_Brick_Included

