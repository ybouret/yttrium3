
//! file

#ifndef Y_Field_Layout4D_Included
#define Y_Field_Layout4D_Included 1

#include "y/field/layout/3d.hpp"
#include "y/mkl/v4d.hpp"

namespace Yttrium
{
    namespace Field
    {
        typedef V4D<unit_t> Coord4D; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! 4D (shared) Layout
        //
        //
        //______________________________________________________________________
        class Layout4D : public Layout<Coord4D>
        {
        public:
            explicit Layout4D(const Coord4D, const Coord4D); //!< setup
            virtual ~Layout4D() noexcept;                    //!< cleanup
            Layout4D(const Layout4D &) noexcept;             //!< duplicate
            const Layout3D sub;                              //!< 3D projection
        private:
            Y_Disable_Assign(Layout4D);                      //!< discarded
        };

    }

}

#endif // !Y_Field_Layout4D_Included

