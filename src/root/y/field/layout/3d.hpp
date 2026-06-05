//! file

#ifndef Y_Field_Layout3D_Included
#define Y_Field_Layout3D_Included 1

#include "y/field/layout/2d.hpp"
#include "y/mkl/v3d.hpp"

namespace Yttrium
{
    namespace Field
    {
        typedef V3D<unit_t> Coord3D; //!< alias


        //______________________________________________________________________
        //
        //
        //
        //! 3D (shared) Layout
        //
        //
        //______________________________________________________________________
        class Layout3D : public Layout<Coord3D>
        {
        public:
            explicit Layout3D(const Coord3D, const Coord3D); //!< setup
            virtual ~Layout3D()        noexcept;             //!< cleanup
            Layout3D(const Layout3D &) noexcept;             //!< duplicate
            const Layout2D sub;                              //!< 2D projection
        private:
            Y_Disable_Assign(Layout3D);                      //!< discarded
        };

    }

}

#endif // !Y_Field_Layout3D_Included

