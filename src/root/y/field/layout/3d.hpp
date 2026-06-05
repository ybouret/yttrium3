//! file

#ifndef Y_Field_Layout3D_Included
#define Y_Field_Layout3D_Included 1

#include "y/field/layout/2d.hpp"
#include "y/mkl/v3d.hpp"

namespace Yttrium
{
    namespace Field
    {
        typedef V3D<unit_t> Coord3D;

        class Layout3D : public Layout<Coord3D>
        {
        public:
            explicit Layout3D(const Coord3D, const Coord3D);
            virtual ~Layout3D() noexcept;
            Layout3D(const Layout3D &) noexcept;

            const Layout2D sub;

        private:
            Y_Disable_Assign(Layout3D);
        };

    }

}

#endif // !Y_Field_Layout3D_Included

