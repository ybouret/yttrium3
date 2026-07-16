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
            explicit Area(const unit_t W, const unit_t H);
            virtual ~Area() noexcept;
            Area(const Area &) noexcept;

            Vertex getUpper() const noexcept;

            const unit_t w;
            const unit_t h;
            const size_t n;
            const unit_t xt;
            const unit_t yt;


        private:
            Y_Disable_Assign(Area);
        };

    }
}

#endif // !Y_Ink_Area_Included

