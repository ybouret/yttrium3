
//! file

#ifndef Y_Field_Layout4D_Included
#define Y_Field_Layout4D_Included 1

#include "y/field/layout/3d.hpp"
#include "y/mkl/v4d.hpp"

namespace Yttrium
{
    namespace Field
    {
        typedef V4D<unit_t> Coord4D;

        class Layout4D : public Layout<Coord4D>
        {
        public:
            explicit Layout4D(const Coord4D, const Coord4D);
            virtual ~Layout4D() noexcept;
            Layout4D(const Layout4D &) noexcept;

            const Layout3D sub;

        private:
            Y_Disable_Assign(Layout4D);
        };

    }

}

#endif // !Y_Field_Layout4D_Included

