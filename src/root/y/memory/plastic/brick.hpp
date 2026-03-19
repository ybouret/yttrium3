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

            //__________________________________________________________________
            //
            //
            //! Brick to pave anonymous memory regions
            //
            //__________________________________________________________________
            struct Brick
            {
                Bricks * used; //!< owner of the memory region
                size_t   size; //!< size in bytes at this+1
                Brick *  next; //!< for list
                Brick *  prev; //!< for list

                static size_t BytesBetween(const Brick * const a,
                                           const Brick * const b) noexcept;

                //! update size using next
                void updateSize() noexcept;

            };
        }
    }
}

#endif // !Y_Memory_Plastic_Brick_Included

