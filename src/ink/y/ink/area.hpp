//! \file

#ifndef Y_Ink_Area_Included
#define Y_Ink_Area_Included 1

#include "y/mkl/v2d.hpp"

namespace Yttrium
{
    namespace Ink
    {

        typedef V2D<unit_t> Vertex;

        class Area
        {
        public:

            virtual ~Area() noexcept;
            
        private:
            Y_Disable_Copy_And_Assign(Area);
        };

    }
}

#endif // !Y_Ink_Area_Included

