
//! \file

#ifndef Y_Memory_Plastic_Forge_Included
#define Y_Memory_Plastic_Forge_Included 1

#include "y/memory/plastic/bricks.hpp"
#include "y/calculus/alignment.hpp"

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
            //
            // Brick to pave anonymous memory regions
            //
            //
            //__________________________________________________________________
            class Forge
            {
            public:
                static const size_t DataOffset = Alignment::To<Brick>::CeilOf<sizeof(Bricks)>::Value;
                explicit Forge();
                virtual ~Forge() noexcept;

            private:
                Y_Disable_Copy_And_Assign(Forge);

            };

        }
    }
}

#endif // !Y_Memory_Plastic_Forge_Included

