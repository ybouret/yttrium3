//! file

#ifndef Y_Field_Layout2D_Included
#define Y_Field_Layout2D_Included 1

#include "y/field/layout/1d.hpp"
#include "y/mkl/v2d.hpp"

namespace Yttrium
{
    namespace Field
    {
        typedef V2D<unit_t> Coord2D;

        class Layout2D : public Layout<Coord2D>
        {
        public:
            explicit Layout2D(const Coord2D, const Coord2D);
            virtual ~Layout2D() noexcept;
            Layout2D(const Layout2D &) noexcept;

            const Layout1D sub;

        private:
            Y_Disable_Assign(Layout2D);
        };

    }

}

#endif // !Y_Field_Layout2D_Included

